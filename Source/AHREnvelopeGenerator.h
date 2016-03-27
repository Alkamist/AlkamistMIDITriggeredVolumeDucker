#ifndef AHRENVELOPEGENERATOR_H_INCLUDED
#define AHRENVELOPEGENERATOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "QuadraticBezierCurve.h"

class AHREnvelopeGenerator
{
public:

    AHREnvelopeGenerator();

    void reset (double inputSampleRate, int inputBlockSize);
    void startEnvelope();
    void processSample();

    // Getters
    double getOutput();
    inline bool envelopeIsFinished()                  { return mEnvelopeIsFinished; };

    // Setters
    inline void setHoldLevel (double input)           { mHoldLevel = input; };
    inline void setAttackTime (double input)          { mAttackTime = input; };
    inline void setHoldTime (double input)            { mHoldTime = input; };
    inline void setReleaseTime (double input)         { mReleaseTime = input; };
    inline void setVelocitySensitivity (double input) { mVelocitySensitivity = input; };
    inline void setStartingLevel (double input)       { mStartingLevel = input; };
    void setVelocityScaleFactor (uint8 velocity);

private:

    double mHoldLevel;
    double mAttackTime;
    double mHoldTime;
    double mReleaseTime;
    double mVelocitySensitivity;

    double mEnvelopeOutput;
    double mStartingLevel;

    double mSampleRate;
    int mBlockSize;

    int mCurrentStageSampleIndex;
    int mNextStageSampleIndex;
    int mCurrentStage;

    double mAdder;
    double mScaleFactor;

    bool mEnvelopeIsFinished;

    void performStateChange();
    //double calculateLogarithmicMultiplier (double startLevel, double endLevel, unsigned int lengthInSamples);
    double calculateLinearAdder (double startLevel, double endLevel, unsigned int lengthInSamples);

    QuadraticBezierCurve mQuadraticBezierCurve;

};

#endif // AHRENVELOPEGENERATOR_H_INCLUDED