#include "SidechainCompressorEnvelope.h"

SidechainCompressorEnvelope::SidechainCompressorEnvelope()
{}

void SidechainCompressorEnvelope::reset (double inputSampleRate, int inputBlockSize)
{
    mSampleRate = inputSampleRate;
    mBlockSize = inputBlockSize;
}

void SidechainCompressorEnvelope::processBlock (AudioSampleBuffer& inputAudioBuffer, MidiBuffer& inputMIDIBuffer)
{
    for (int channel = 0; channel < inputAudioBuffer.getNumChannels(); ++channel)
    {
        float* channelData = inputAudioBuffer.getWritePointer (channel);

        for (int sample = 0; sample < mBlockSize; ++sample)
        {
            float temporaryGain = (mHoldLevel[sample] / 60.0f) + 1.0f;
            channelData[sample] = temporaryGain;
        }
    }
}