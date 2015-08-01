/*
  ==============================================================================

    EnvelopeVoiceManager.cpp
    Created: 31 Jul 2015 3:36:25pm
    Author:  Corey

  ==============================================================================
*/

#include "AHREnvelopeGenerator.h"

#include "EnvelopeVoiceManager.h"

EnvelopeVoiceManager::EnvelopeVoiceManager()
    : mOutput (1.0f),
      mListOfEnvelopes (2)
{}

// This function returns a pointer to the envelope that has the
// smallest output.
AHREnvelopeGenerator* findSmallestEnvelopeOutput (std::vector<AHREnvelopeGenerator*> inputVector)
{
    float smallestOutput = 1.0f;
    AHREnvelopeGenerator* envelopeWithSmallestOutput = nullptr;

    for (int index = 0; index < inputVector.size(); ++index)
    {
        inputVector[index]->processEnvelope();
        if (inputVector[index]->getOutput() < smallestOutput)
        {
            smallestOutput = inputVector[index]->getOutput();
            envelopeWithSmallestOutput = inputVector[index];
        }
    }

    return envelopeWithSmallestOutput;
}

// This function finds the envelope with the smallest output,
// and then sets the voice manager's output to that
// envelope's output.
void EnvelopeVoiceManager::process()
{
    AHREnvelopeGenerator* envelopeWithSmallestOutput;
    envelopeWithSmallestOutput = findSmallestEnvelopeOutput (mListOfEnvelopes);

    mOutput = envelopeWithSmallestOutput->getOutput();
}

// This function returns a pointer to the envelope that is closest
// to being done.
AHREnvelopeGenerator* findCloseToOrCompletedEnvelope (std::vector<AHREnvelopeGenerator*> inputVector)
{
    int largestEnvelopeIndex = 0;
    AHREnvelopeGenerator* mostCompleteEnvelope = nullptr;

    for (int index = 0; index < inputVector.size(); ++index)
    {
        if (inputVector[index]->getEnvelopeSampleIndex() > largestEnvelopeIndex)
        {
            largestEnvelopeIndex = inputVector[index]->getEnvelopeSampleIndex();
            mostCompleteEnvelope = inputVector[index];
        }
    }

    return mostCompleteEnvelope;
}

// This function starts an envelope using an available voice,
// or restarts the most complete envelope if there isn't one.
// It also sets the MIDI velocity scale factor of the envelope
// that is being used.
void EnvelopeVoiceManager::startEnvelopeUsingAvailableVoice (const MidiMessage& inputMidiMessage)
{
    AHREnvelopeGenerator* mostCompleteEnvelope;
    mostCompleteEnvelope = findCloseToOrCompletedEnvelope(mListOfEnvelopes);

    mostCompleteEnvelope->restartEnvelope();
    mostCompleteEnvelope->setVelocityScaleFactor (inputMidiMessage.getVelocity());
}

//=============================================================

void EnvelopeVoiceManager::setHoldLevel (float input)
{
    for (int index = 0; index < mListOfEnvelopes.size(); ++index)
    {
        mListOfEnvelopes[index]->setHoldLevel (input);
    }
}

void EnvelopeVoiceManager::setAttackTime (float input)
{
    for (int index = 0; index < mListOfEnvelopes.size(); ++index)
    {
        mListOfEnvelopes[index]->setAttackTime (input);
    }
}

void EnvelopeVoiceManager::setHoldTime (float input)
{
    for (int index = 0; index < mListOfEnvelopes.size(); ++index)
    {
        mListOfEnvelopes[index]->setHoldTime (input);
    }
}

void EnvelopeVoiceManager::setReleaseTime (float input)
{
    for (int index = 0; index < mListOfEnvelopes.size(); ++index)
    {
        mListOfEnvelopes[index]->setReleaseTime (input);
    }
}

void EnvelopeVoiceManager::setVelocitySensitivity (float input)
{
    for (int index = 0; index < mListOfEnvelopes.size(); ++index)
    {
        mListOfEnvelopes[index]->setVelocitySensitivity (input);
    }
}

void EnvelopeVoiceManager::setSampleRate (float input)
{
    for (int index = 0; index < mListOfEnvelopes.size(); ++index)
    {
        mListOfEnvelopes[index]->setHoldLevel (input);
    }
}
