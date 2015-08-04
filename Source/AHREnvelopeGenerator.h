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
    double calculateMultiplier(double startLevel, double endLevel, int lengthInSamples);

    // Getters
    inline double getOutput() { return mEnvelopeOutput; };
    inline int getEnvelopeSampleIndex() { return mEnvelopeSampleIndex; };

    // Setters
    inline void setHoldLevel (double input)           { mHoldLevel = input; };
    inline void setAttackTime (double input)          { mAttackTime = input; };
    inline void setHoldTime (double input)            { mHoldTime = input; };
    inline void setReleaseTime (double input)         { mReleaseTime = input; };
    inline void setVelocitySensitivity (double input) { mVelocitySensitivity = input; };
    inline void setSampleRate (double input)          { mSampleRate = input; };

private:

    // Controls
    double mHoldLevel;
    double mAttackTime;
    double mHoldTime;
    double mReleaseTime;
    double mVelocitySensitivity;
    double mEnvelopeOutput;

    // Members
    int mSampleRate;
    int mCurrentStageSampleIndex;
    int mNextStageSampleIndex;
    int mCurrentStage;
    double mMultiplier;
    double mScaleFactor;
    int mEnvelopeSampleIndex;

};

#endif