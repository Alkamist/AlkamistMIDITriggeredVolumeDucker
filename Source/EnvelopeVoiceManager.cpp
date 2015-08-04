#include "AHREnvelopeGenerator.h"

#include "EnvelopeVoiceManager.h"

EnvelopeVoiceManager::EnvelopeVoiceManager()
    : mOutput (1.0f)
{
    for (int index = 0; index < kMaxNumberOfVoices; ++index)
    {
        mListOfEnvelopes[index] = new AHREnvelopeGenerator();
    }
}

// This function returns a pointer to the envelope that has the
// smallest output.
AHREnvelopeGenerator* findEnvelopeWithSmallestOutput (AHREnvelopeGenerator* inputArray[])
{
    AHREnvelopeGenerator* envelopeWithSmallestOutput;
    double smallestOutput = 1.1f;

    for (int index = 0; index < kMaxNumberOfVoices; ++index)
    {
        inputArray[index]->processEnvelope();
        double currentArrayOutput = inputArray[index]->getOutput();

        if (currentArrayOutput <= smallestOutput)
        {
            smallestOutput = currentArrayOutput;
            envelopeWithSmallestOutput = inputArray[index];
        }
    }

    return envelopeWithSmallestOutput;
}

// This function finds the envelope with the smallest output,
// and then sets the voice manager's output to that
// envelope's output.
void EnvelopeVoiceManager::processPerSample()
{  
    AHREnvelopeGenerator* envelopeWithSmallestOutput = findEnvelopeWithSmallestOutput (mListOfEnvelopes);

    mOutput = envelopeWithSmallestOutput->getOutput();
}

// This function returns a pointer to the envelope that is closest
// to being done.
AHREnvelopeGenerator* findMostCompleteEnvelope (AHREnvelopeGenerator* inputArray[])
{
    AHREnvelopeGenerator* mostCompleteEnvelope;
    int largestEnvelopeSampleIndex = 0;

    for (int index = 0; index < kMaxNumberOfVoices; ++index)
    {
        double currentEnvelopeSampleIndex = inputArray[index]->getEnvelopeSampleIndex();

        if (currentEnvelopeSampleIndex >= largestEnvelopeSampleIndex)
        {
            largestEnvelopeSampleIndex = currentEnvelopeSampleIndex;
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
    AHREnvelopeGenerator* mostCompleteEnvelope = findMostCompleteEnvelope (mListOfEnvelopes);

    mostCompleteEnvelope->restartEnvelope();
    mostCompleteEnvelope->setVelocityScaleFactor (inputMidiMessage.getVelocity());
}

//=============================================================

void EnvelopeVoiceManager::setHoldLevel (double input)
{
    for (int index = 0; index < kMaxNumberOfVoices; ++index)
    {
        mListOfEnvelopes[index]->setHoldLevel (input);
    }
}

void EnvelopeVoiceManager::setAttackTime (double input)
{
    for (int index = 0; index < kMaxNumberOfVoices; ++index)
    {
        mListOfEnvelopes[index]->setAttackTime (input);
    }
}

void EnvelopeVoiceManager::setHoldTime (double input)
{
    for (int index = 0; index < kMaxNumberOfVoices; ++index)
    {
        mListOfEnvelopes[index]->setHoldTime (input);
    }
}

void EnvelopeVoiceManager::setReleaseTime (double input)
{
    for (int index = 0; index < kMaxNumberOfVoices; ++index)
    {
        mListOfEnvelopes[index]->setReleaseTime (input);
    }
}

void EnvelopeVoiceManager::setVelocitySensitivity (double input)
{
    for (int index = 0; index < kMaxNumberOfVoices; ++index)
    {
        mListOfEnvelopes[index]->setVelocitySensitivity (input);
    }
}

void EnvelopeVoiceManager::reset (double inputSampleRate)
{
    for (int index = 0; index < kMaxNumberOfVoices; ++index)
    {
        mListOfEnvelopes[index]->setSampleRate (inputSampleRate);
    }
}
