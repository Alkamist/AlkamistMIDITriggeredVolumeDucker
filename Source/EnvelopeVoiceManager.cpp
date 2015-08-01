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
    : mOutput (1.0f)
{
    for (int index = 0; index < maxNumberOfVoices; ++index)
    {
        mListOfEnvelopes[index] = new AHREnvelopeGenerator();
    }
}

// This function returns a pointer to the envelope that has the
// smallest output.
AHREnvelopeGenerator* findSmallestEnvelopeOutput (AHREnvelopeGenerator* inputArray[])
{
    float smallestOutput = 1.1f;
    AHREnvelopeGenerator* envelopeWithSmallestOutput;

    for (int index = 0; index < maxNumberOfVoices; ++index)
    {
        inputArray[index]->processEnvelope();
        if (inputArray[index]->getOutput() <= smallestOutput)
        {
            smallestOutput = inputArray[index]->getOutput();
            envelopeWithSmallestOutput = inputArray[index];
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
AHREnvelopeGenerator* findMostCompleteEnvelope (AHREnvelopeGenerator* inputArray[])
{
    int largestEnvelopeIndex = 0;
    AHREnvelopeGenerator* mostCompleteEnvelope;

    for (int index = 0; index < maxNumberOfVoices; ++index)
    {
        if (inputArray[index]->getEnvelopeSampleIndex() >= largestEnvelopeIndex)
        {
            largestEnvelopeIndex = inputArray[index]->getEnvelopeSampleIndex();
            mostCompleteEnvelope = inputArray[index];
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
    mostCompleteEnvelope = findMostCompleteEnvelope (mListOfEnvelopes);

    mostCompleteEnvelope->restartEnvelope();
    mostCompleteEnvelope->setVelocityScaleFactor (inputMidiMessage.getVelocity());
}

//=============================================================

void EnvelopeVoiceManager::setHoldLevel (float input)
{
    for (int index = 0; index < maxNumberOfVoices; ++index)
    {
        mListOfEnvelopes[index]->setHoldLevel (input);
    }
}

void EnvelopeVoiceManager::setAttackTime (float input)
{
    for (int index = 0; index < maxNumberOfVoices; ++index)
    {
        mListOfEnvelopes[index]->setAttackTime (input);
    }
}

void EnvelopeVoiceManager::setHoldTime (float input)
{
    for (int index = 0; index < maxNumberOfVoices; ++index)
    {
        mListOfEnvelopes[index]->setHoldTime (input);
    }
}

void EnvelopeVoiceManager::setReleaseTime (float input)
{
    for (int index = 0; index < maxNumberOfVoices; ++index)
    {
        mListOfEnvelopes[index]->setReleaseTime (input);
    }
}

void EnvelopeVoiceManager::setVelocitySensitivity (float input)
{
    for (int index = 0; index < maxNumberOfVoices; ++index)
    {
        mListOfEnvelopes[index]->setVelocitySensitivity (input);
    }
}

void EnvelopeVoiceManager::setSampleRate (float input)
{
    for (int index = 0; index < maxNumberOfVoices; ++index)
    {
        mListOfEnvelopes[index]->setHoldLevel (input);
    }
}
