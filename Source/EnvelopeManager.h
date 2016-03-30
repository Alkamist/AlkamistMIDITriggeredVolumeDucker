#ifndef ENVELOPEMANAGER_H_INCLUDED
#define ENVELOPEMANAGER_H_INCLUDED

#include <vector>

#include "../JuceLibraryCode/JuceHeader.h"
#include "AHREnvelopeGenerator.h"

class EnvelopeManager
{
public:

    EnvelopeManager();

    void reset (double inputSampleRate, int inputBlockSize);
    void processBlock (AudioSampleBuffer& inputAudioBuffer, MidiBuffer& inputMIDIBuffer);

    // Setters:
    inline void setHoldLevel (const std::vector<float>& input)         { mHoldLevel = input; };
    inline void setAttackTime (const std::vector<float>& input)        { mAttackTime = input; };
    inline void setReleaseTime (const std::vector<float>& input)       { mReleaseTime = input; };

private:

    std::vector<double> mOutputBuffer;
    double mLastOutputSample;

    AudioSampleBuffer* mAudioBufferIn;
    MidiBuffer* mMIDIBufferIn;

    double mSampleRate;
    int mBlockSize;

    int mCurrentSampleInBlock;

    // Buffered Parameters:
    std::vector<float> mHoldLevel;
    std::vector<float> mAttackTime;
    std::vector<float> mReleaseTime;

    std::vector<AHREnvelopeGenerator> mEnvelopeContainer;

    void bufferEnvelope();
    void startNewEnvelope (MidiMessage& inputMIDIMessage);

};

#endif  // ENVELOPEMANAGER_H_INCLUDED
