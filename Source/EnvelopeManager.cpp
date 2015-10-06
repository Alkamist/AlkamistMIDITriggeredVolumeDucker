#include <cmath>

#include "EnvelopeManager.h"

EnvelopeManager::EnvelopeManager()
{}

void EnvelopeManager::reset (double inputSampleRate, int inputBlockSize)
{
    mSampleRate = inputSampleRate;
    mBlockSize = inputBlockSize;

    mOutputBuffer.resize (inputBlockSize);
    mHoldLevel.resize (inputBlockSize);
    mAttackTime.resize (inputBlockSize);
    mHoldTime.resize (inputBlockSize);
    mReleaseTime.resize (inputBlockSize);
    mVelocitySensitivity.resize (inputBlockSize);

    if (! mEnvelopeContainer.empty())
    {
        for (int envelopeIndex = 0; envelopeIndex < mEnvelopeContainer.size(); ++envelopeIndex)
        {
            mEnvelopeContainer[envelopeIndex].reset (inputSampleRate, inputBlockSize);
        }
    }
}

void EnvelopeManager::processBlock (AudioSampleBuffer& inputAudioBuffer, MidiBuffer& inputMIDIBuffer)
{
    mAudioBufferIn = &inputAudioBuffer;
    mMIDIBufferIn = &inputMIDIBuffer;

    bufferEnvelope();

    for (int channel = 0; channel < inputAudioBuffer.getNumChannels(); ++channel)
    {
        float* channelData = inputAudioBuffer.getWritePointer (channel);

        for (int sample = 0; sample < mBlockSize; ++sample)
        {
            float temporaryGain = mOutputBuffer[sample];
            channelData[sample] *= temporaryGain;
        }
    }
}

void EnvelopeManager::bufferEnvelope()
{
    MidiBuffer::Iterator MIDIMessagesIterator (*mMIDIBufferIn);
    MidiMessage currentMidiMessage;
    int midiMessageSamplePosition = 0;

    if (! mMIDIBufferIn->isEmpty())
    {
        MIDIMessagesIterator.getNextEvent (currentMidiMessage, midiMessageSamplePosition);
    }

    for (int sample = 0; sample < mBlockSize; ++sample)
    {
        mCurrentSampleInBlock = sample;

        // MIDI Implementation:
        if (! mMIDIBufferIn->isEmpty())
        {
            bool midiBufferIsNotEmpty = true;
            bool alreadyHadNoteOn = false;

            while (sample == midiMessageSamplePosition
                   && midiBufferIsNotEmpty)
            {
                if (currentMidiMessage.isNoteOn()
                    && ! alreadyHadNoteOn)
                {
                    startNewEnvelope (currentMidiMessage);
                    alreadyHadNoteOn = true;
                }

                midiBufferIsNotEmpty = MIDIMessagesIterator.getNextEvent (currentMidiMessage, midiMessageSamplePosition);
            }
        }
    
        // Envelope Comparison:
        if (! mEnvelopeContainer.empty())
        {
            AHREnvelopeGenerator* envelopeWithSmallestOutput = nullptr;
            double smallestOutput = 1.1;

            for (int index = 0; index < mEnvelopeContainer.size(); ++index)
            {
                if (mEnvelopeContainer[index].envelopeIsFinished())
                {
                    mEnvelopeContainer.erase (mEnvelopeContainer.begin() + index);
                    --index;
                }
                else
                {
                    mEnvelopeContainer[index].processSample();
                    double currentEnvelopeOutput = mEnvelopeContainer[index].getOutput();

                    if (currentEnvelopeOutput <= smallestOutput)
                    {
                        smallestOutput = currentEnvelopeOutput;
                        envelopeWithSmallestOutput = &mEnvelopeContainer[index];
                    }
                }
            }

            if (envelopeWithSmallestOutput == nullptr)
            {
                mOutputBuffer[sample] = 1.0;
            }
            else
            {
                mOutputBuffer[sample] = envelopeWithSmallestOutput->getOutput();
            }
        }
        else
        {
            mOutputBuffer[sample] = 1.0;
        }

        mLastOutputSample = mOutputBuffer[sample];
    }
}

void EnvelopeManager::startNewEnvelope (MidiMessage& inputMIDIMessage)
{
    AHREnvelopeGenerator freshEnvelope;

    freshEnvelope.reset (mSampleRate, mBlockSize);

    freshEnvelope.setHoldLevel (mHoldLevel[mCurrentSampleInBlock]);
    freshEnvelope.setAttackTime (mAttackTime[mCurrentSampleInBlock]);
    freshEnvelope.setHoldTime (mHoldTime[mCurrentSampleInBlock]);
    freshEnvelope.setReleaseTime (mReleaseTime[mCurrentSampleInBlock]);
    freshEnvelope.setVelocitySensitivity (mVelocitySensitivity[mCurrentSampleInBlock]);
    freshEnvelope.setVelocityScaleFactor (inputMIDIMessage.getVelocity());

    freshEnvelope.setStartingLevel (mLastOutputSample);
    freshEnvelope.startEnvelope();

    mEnvelopeContainer.push_back (freshEnvelope);
}