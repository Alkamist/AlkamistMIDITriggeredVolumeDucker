/*
  ==============================================================================

    EnvelopeVoiceManager.h
    Created: 31 Jul 2015 3:36:25pm
    Author:  Corey

  ==============================================================================
*/

#ifndef ENVELOPEVOICEMANAGER_H_INCLUDED
#define ENVELOPEVOICEMANAGER_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class AHREnvelopeGenerator;

const int kMaxNumberOfVoices = 32;

class EnvelopeVoiceManager
{
public:
    EnvelopeVoiceManager();

    void processPerSample();
    void startEnvelopeUsingAvailableVoice (const MidiMessage& inputMidiMessage);

    inline double getOutput() { return mOutput; };

    void setHoldLevel (double input);
    void setAttackTime (double input);
    void setHoldTime (double input);
    void setReleaseTime (double input);
    void setVelocitySensitivity (double input);

    void reset (double inputSampleRate);
private:
    double mOutput;

    AHREnvelopeGenerator* mListOfEnvelopes[kMaxNumberOfVoices];
};

#endif  // ENVELOPEVOICEMANAGER_H_INCLUDED
