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
    inline void setHoldLevel (const std::vector<float>& input)           { mHoldLevel = input; };
    inline void setAttackTime (const std::vector<float>& input)          { mAttackTime = input; };
    inline void setReleaseTime (const std::vector<float>& input)         { mReleaseTime = input; };
    inline void setAttackBottomWeight (const std::vector<float>& input)  { mAttackBottomWeight = input; };
    inline void setAttackTopWeight (const std::vector<float>& input)     { mAttackTopWeight = input; };
    inline void setReleaseBottomWeight (const std::vector<float>& input) { mReleaseBottomWeight = input; };
    inline void setReleaseTopWeight (const std::vector<float>& input)    { mReleaseTopWeight = input; };

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
    std::vector<float> mAttackBottomWeight;
    std::vector<float> mAttackTopWeight;
    std::vector<float> mReleaseBottomWeight;
    std::vector<float> mReleaseTopWeight;

    std::vector<AHREnvelopeGenerator> mEnvelopeContainer;

    void bufferEnvelope();
    void startNewEnvelope (MidiMessage& inputMIDIMessage);

};

#endif  // ENVELOPEMANAGER_H_INCLUDED
