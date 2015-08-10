#include "EnvelopeVoiceManager.h"

EnvelopeVoiceManager::EnvelopeVoiceManager()
    : mOutput (1.0),
      mHoldLevel (1.0),
      mAttackTime (0.1),
      mHoldTime (0.1),
      mReleaseTime (0.1),
      mVelocitySensitivity (1.0),
      mSampleRate (44100.0),
      mCurrentEnvelope (0),
      mThereAreEnvelopesRunning (false)
{
    for (int index = 0; index < mMaxNumberOfVoices; ++index)
    {
        mEnvelopeContainer[index].setVoiceManager (this);
    }
}

void EnvelopeVoiceManager::processPerSample()
{  
    if (mThereAreEnvelopesRunning)
    {
        AHREnvelopeGenerator* envelopeWithSmallestOutput = nullptr;
        double smallestOutput = 1.1;

        for (int index = 0; index < mMaxNumberOfVoices; ++index)
        {
            if (!mEnvelopeContainer[index].envelopeIsFinished())
            {
                mEnvelopeContainer[index].processPerSample();
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
            mThereAreEnvelopesRunning = false;
            mOutput = 1.0;
        }
        else
        {
            mOutput = envelopeWithSmallestOutput->getOutput();
        }
    }
}

void EnvelopeVoiceManager::startNewEnvelope (const MidiMessage& inputMidiMessage)
{
    mEnvelopeContainer[mCurrentEnvelope].setHoldLevel (mHoldLevel);
    mEnvelopeContainer[mCurrentEnvelope].setAttackTime (mAttackTime);
    mEnvelopeContainer[mCurrentEnvelope].setHoldTime (mHoldTime);
    mEnvelopeContainer[mCurrentEnvelope].setReleaseTime (mReleaseTime);
    mEnvelopeContainer[mCurrentEnvelope].setVelocitySensitivity (mVelocitySensitivity);
    mEnvelopeContainer[mCurrentEnvelope].setSampleRate (mSampleRate);
    mEnvelopeContainer[mCurrentEnvelope].setVelocityScaleFactor (inputMidiMessage.getVelocity());

    mEnvelopeContainer[mCurrentEnvelope].startEnvelope();

    ++mCurrentEnvelope;

    if (mCurrentEnvelope >= mMaxNumberOfVoices)
        mCurrentEnvelope = 0;

    mThereAreEnvelopesRunning = true;
}

//=============================================================
void EnvelopeVoiceManager::setHoldLevel (double input)
{
    mHoldLevel = input;
}

void EnvelopeVoiceManager::setAttackTime (double input)
{
    mAttackTime = input;
}

void EnvelopeVoiceManager::setHoldTime (double input)
{
    mHoldTime = input;
}

void EnvelopeVoiceManager::setReleaseTime (double input)
{
    mReleaseTime = input;
}

void EnvelopeVoiceManager::setVelocitySensitivity (double input)
{
    mVelocitySensitivity = input;
}

void EnvelopeVoiceManager::reset (double inputSampleRate)
{
    mSampleRate = inputSampleRate;
}
