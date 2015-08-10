#ifndef __AHR_ENVELOPE_GENERATOR_H__
#define __AHR_ENVELOPE_GENERATOR_H__

#include "../JuceLibraryCode/JuceHeader.h"

class EnvelopeVoiceManager;

class AHREnvelopeGenerator
{
public:

    AHREnvelopeGenerator();

    void startEnvelope();
    void processPerSample();
    void setVelocityScaleFactor (uint8 velocity);

    // Getters
    inline double getOutput()                         { return mEnvelopeOutput; };
    inline int getEnvelopeSampleIndex()               { return mEnvelopeSampleIndex; };
    inline bool envelopeIsFinished()                  { return mEnvelopeIsFinished; };

    // Setters
    inline void setHoldLevel (double input)                               { mHoldLevel = input; };
    inline void setAttackTime (double input)                              { mAttackTime = input; };
    inline void setHoldTime (double input)                                { mHoldTime = input; };
    inline void setReleaseTime (double input)                             { mReleaseTime = input; };
    inline void setVelocitySensitivity (double input)                     { mVelocitySensitivity = input; };
    inline void setSampleRate (double input)                              { mSampleRate = input; };
    inline void setVoiceManager (EnvelopeVoiceManager* inputVoiceManager) { mVoiceManager = inputVoiceManager; };

private:

    EnvelopeVoiceManager* mVoiceManager;

    double mHoldLevel;
    double mAttackTime;
    double mHoldTime;
    double mReleaseTime;
    double mVelocitySensitivity;
    double mEnvelopeOutput;
    double mSampleRate;
    int mCurrentStageSampleIndex;
    int mNextStageSampleIndex;
    int mCurrentStage;
    double mMultiplier;
    double mScaleFactor;
    int mEnvelopeSampleIndex;
    bool mEnvelopeIsFinished;

    void performStateChange();
    double calculateMultiplier(double startLevel, double endLevel, int lengthInSamples);

};

#endif