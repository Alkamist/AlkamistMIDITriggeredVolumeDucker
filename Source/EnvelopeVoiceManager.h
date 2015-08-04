#ifndef ENVELOPEVOICEMANAGER_H_INCLUDED
#define ENVELOPEVOICEMANAGER_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class AHREnvelopeGenerator;

const int kMaxNumberOfVoices = 64;

class EnvelopeVoiceManager
{
public:

    EnvelopeVoiceManager();

    void reset (double inputSampleRate);
    void processPerSample();
    void startEnvelopeUsingAvailableVoice (const MidiMessage& inputMidiMessage);

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

    AHREnvelopeGenerator* mListOfEnvelopes[kMaxNumberOfVoices];

};

#endif  // ENVELOPEVOICEMANAGER_H_INCLUDED
