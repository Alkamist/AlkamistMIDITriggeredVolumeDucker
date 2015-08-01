/*
  ==============================================================================

    EnvelopeVoiceManager.h
    Created: 31 Jul 2015 3:36:25pm
    Author:  Corey

  ==============================================================================
*/

#ifndef ENVELOPEVOICEMANAGER_H_INCLUDED
#define ENVELOPEVOICEMANAGER_H_INCLUDED

#include <vector>

#include "../JuceLibraryCode/JuceHeader.h"

class AHREnvelopeGenerator;

class EnvelopeVoiceManager
{
public:
    EnvelopeVoiceManager();

    void process();
    void startEnvelopeUsingAvailableVoice (const MidiMessage& inputMidiMessage);

    inline float getOutput() { return mOutput; };

    void setHoldLevel (float input);
    void setAttackTime (float input);
    void setHoldTime (float input);
    void setReleaseTime (float input);
    void setVelocitySensitivity (float input);
    void setSampleRate (float input);
private:
    float mOutput;

    std::vector<AHREnvelopeGenerator*> mListOfEnvelopes;
};

#endif  // ENVELOPEVOICEMANAGER_H_INCLUDED
