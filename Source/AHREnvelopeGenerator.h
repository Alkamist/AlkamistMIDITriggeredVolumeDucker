#ifndef __AHR_ENVELOPE_GENERATOR_H__
#define __AHR_ENVELOPE_GENERATOR_H__

#include "../JuceLibraryCode/JuceHeader.h"

class AHREnvelopeGenerator
{
public:
    AHREnvelopeGenerator();

    void restartEnvelope();
    void processEnvelope();
    void setVelocityScaleFactor (uint8 velocity);
    float calculateMultiplier(float startLevel, float endLevel, int lengthInSamples);

    // Getters
    inline float getOutput() { return mEnvelopeOutput; };
    inline int getEnvelopeSampleIndex() { return mEnvelopeSampleIndex; };

    // Setters
    inline void setHoldLevel (float input)           { mHoldLevel = input; };
    inline void setAttackTime (float input)          { mAttackTime = input; };
    inline void setHoldTime (float input)            { mHoldTime = input; };
    inline void setReleaseTime (float input)         { mReleaseTime = input; };
    inline void setVelocitySensitivity (float input) { mVelocitySensitivity = input; };
    inline void setSampleRate (float input)          { mSampleRate = input; };
private:
    // Controls
    float mHoldLevel;
    float mAttackTime;
    float mHoldTime;
    float mReleaseTime;
    float mVelocitySensitivity;
    float mEnvelopeOutput;

    // Members
    int mSampleRate;
    int mCurrentStageSampleIndex;
    int mNextStageSampleIndex;
    int mCurrentStage;
    float mMultiplier;
    float mScaleFactor;
    int mEnvelopeSampleIndex;
};

#endif