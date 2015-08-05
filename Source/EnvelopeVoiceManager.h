#ifndef ENVELOPEVOICEMANAGER_H_INCLUDED
#define ENVELOPEVOICEMANAGER_H_INCLUDED

#include <deque>

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

    std::deque< ScopedPointer<AHREnvelopeGenerator> > mEnvelopeContainer;

};

#endif  // ENVELOPEVOICEMANAGER_H_INCLUDED
