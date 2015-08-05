#ifndef __AHR_ENVELOPE_GENERATOR_H__
#define __AHR_ENVELOPE_GENERATOR_H__

#include "../JuceLibraryCode/JuceHeader.h"

class AHREnvelopeGenerator
{
public:

    AHREnvelopeGenerator();

    void startEnvelope();
    void processEnvelope();
    void processPerSample();
    void setVelocityScaleFactor (uint8 velocity);
    double calculateMultiplier(double startLevel, double endLevel, int lengthInSamples);

    // Getters
    inline double getOutput()                         { return mEnvelopeOutput; };
    inline int getEnvelopeSampleIndex()               { return mEnvelopeSampleIndex; };
    inline bool envelopeIsFinished()                  { return mEnvelopeIsFinished; };

    // Setters
    inline void setHoldLevel (double input)           { mHoldLevel = input; };
    inline void setAttackTime (double input)          { mAttackTime = input; };
    inline void setHoldTime (double input)            { mHoldTime = input; };
    inline void setReleaseTime (double input)         { mReleaseTime = input; };
    inline void setVelocitySensitivity (double input) { mVelocitySensitivity = input; };
    inline void setSampleRate (double input)          { mSampleRate = input; };

private:

    double mHoldLevel;
    double mAttackTime;
    double mHoldTime;
    double mReleaseTime;
    double mVelocitySensitivity;
    double mEnvelopeOutput;
    int mSampleRate;
    int mCurrentStageSampleIndex;
    int mNextStageSampleIndex;
    int mCurrentStage;
    double mMultiplier;
    double mScaleFactor;
    int mEnvelopeSampleIndex;
    bool mEnvelopeIsFinished;

    void performStateChange();

};

#endif