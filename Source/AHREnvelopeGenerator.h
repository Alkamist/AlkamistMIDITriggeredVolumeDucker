#ifndef AHRENVELOPEGENERATOR_H_INCLUDED
#define AHRENVELOPEGENERATOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "BezierCurve.h"

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
    inline void setReleaseTime (double input)         { mReleaseTime = input; };
    inline void setAttackBottomWeight (double input)  { mAttackBottomWeight = input; };
    inline void setAttackTopWeight (double input)     { mAttackTopWeight = input; };
    inline void setReleaseBottomWeight (double input) { mReleaseBottomWeight = input; };
    inline void setReleaseTopWeight (double input)    { mReleaseTopWeight = input; };

    inline void setStartingLevel (double input)     { mStartingLevel = input; };
    void setVelocityScaleFactor (uint8 velocity);

private:

    double mHoldLevel;
    double mAttackTime;
    double mHoldTime;
    double mReleaseTime;
    double mAttackBottomWeight;
    double mAttackTopWeight;
    double mReleaseBottomWeight;
    double mReleaseTopWeight;

    double mEnvelopeOutput;
    double mStartingLevel;

    double mSampleRate;
    int mBlockSize;

    int mCurrentStageSampleIndex;
    int mNextStageSampleIndex;
    int mCurrentStage;

    double mScaleFactor;

    bool mEnvelopeIsFinished;

    void performStateChange();

    BezierCurve mBezierCurve;

};

#endif // AHRENVELOPEGENERATOR_H_INCLUDED