#ifndef ENVELOPEVOICEMANAGER_H_INCLUDED
#define ENVELOPEVOICEMANAGER_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

#include "AHREnvelopeGenerator.h"

class EnvelopeVoiceManager
{
public:

    EnvelopeVoiceManager();

    void reset (double inputSampleRate);
    void processPerSample();
    void startNewEnvelope (const MidiMessage& inputMidiMessage);

    // Getters
    inline double getOutput() { return mOutput; };

    // Setters
    void setHoldLevel (double input);
    void setAttackTime (double input);
    void setHoldTime (double input);
    void setReleaseTime (double input);
    void setVelocitySensitivity (double input);

private:

    double mOutput;

    double mHoldLevel;
    double mAttackTime;
    double mHoldTime;
    double mReleaseTime;
    double mVelocitySensitivity;
    double mSampleRate;
    
    int mCurrentEnvelope;
    bool mThereAreEnvelopesRunning;

    static const int mMaxNumberOfVoices = 16;

    AHREnvelopeGenerator mEnvelopeContainer[mMaxNumberOfVoices];

    AHREnvelopeGenerator* findEnvelopeWithSmallestOutput();

};

#endif  // ENVELOPEVOICEMANAGER_H_INCLUDED
