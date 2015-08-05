#include "EnvelopeVoiceManager.h"

EnvelopeVoiceManager::EnvelopeVoiceManager()
    : mOutput (1.0),
      mHoldLevel (1.0),
      mAttackTime (0.1),
      mHoldTime (0.1),
      mReleaseTime (0.1),
      mVelocitySensitivity (1.0),
      mSampleRate (44100.0)
{}

// This function returns a pointer to the envelope that has the
// smallest output.
AHREnvelopeGenerator* findEnvelopeWithSmallestOutput (std::deque< ScopedPointer<AHREnvelopeGenerator> >& inputEnvelopeContainer)
{
    AHREnvelopeGenerator* envelopeWithSmallestOutput;
    double smallestOutput = 1.1;

    std::deque< ScopedPointer<AHREnvelopeGenerator> >::iterator dequeIterator = inputEnvelopeContainer.begin();
        
    while (dequeIterator != inputEnvelopeContainer.end())
    {
        (*dequeIterator)->processEnvelope();
        double currentEnvelopeOutput = (*dequeIterator)->getOutput();

        if (currentEnvelopeOutput <= smallestOutput)
        {
            smallestOutput = currentEnvelopeOutput;
            envelopeWithSmallestOutput = (*dequeIterator);
        }

        ++dequeIterator;
    }

    return envelopeWithSmallestOutput;
}

void EnvelopeVoiceManager::processPerSample()
{  
    if (mEnvelopeContainer.empty() == false)
    {
        AHREnvelopeGenerator* envelopeWithSmallestOutput = findEnvelopeWithSmallestOutput (mEnvelopeContainer);
        mOutput = envelopeWithSmallestOutput->getOutput();

        if (mEnvelopeContainer.back()->envelopeIsFinished())
        {
            mEnvelopeContainer.pop_back();
        }
    }
    else
    {
        mOutput = 1.0;
    }
}

void EnvelopeVoiceManager::startNewEnvelope (const MidiMessage& inputMidiMessage)
{
    mEnvelopeContainer.push_front (new AHREnvelopeGenerator());

    AHREnvelopeGenerator* newestEnvelope = mEnvelopeContainer.front();

    // Initialize the new envelope.
    newestEnvelope->setHoldLevel (mHoldLevel);
    newestEnvelope->setAttackTime (mAttackTime);
    newestEnvelope->setHoldTime (mHoldTime);
    newestEnvelope->setReleaseTime (mReleaseTime);
    newestEnvelope->setVelocitySensitivity (mVelocitySensitivity);
    newestEnvelope->setSampleRate (mSampleRate);
    newestEnvelope->restartEnvelope();
    newestEnvelope->setVelocityScaleFactor (inputMidiMessage.getVelocity());
}

//=============================================================
void EnvelopeVoiceManager::setHoldLevel (double input)
{
    mHoldLevel = input;

    if (mEnvelopeContainer.empty() == false)
    {
        std::deque< ScopedPointer<AHREnvelopeGenerator> >::iterator dequeIterator = mEnvelopeContainer.begin();
        
        while (dequeIterator != mEnvelopeContainer.end())
        {
            (*dequeIterator)->setHoldLevel (input);
            ++dequeIterator;
        }
    }
}

void EnvelopeVoiceManager::setAttackTime (double input)
{
    mAttackTime = input;

    if (mEnvelopeContainer.empty() == false)
    {
        std::deque< ScopedPointer<AHREnvelopeGenerator> >::iterator dequeIterator = mEnvelopeContainer.begin();
        
        while (dequeIterator != mEnvelopeContainer.end())
        {
            (*dequeIterator)->setAttackTime (input);
            ++dequeIterator;
        }
    }
}

void EnvelopeVoiceManager::setHoldTime (double input)
{
    mHoldTime = input;

    if (mEnvelopeContainer.empty() == false)
    {
        std::deque< ScopedPointer<AHREnvelopeGenerator> >::iterator dequeIterator = mEnvelopeContainer.begin();
        
        while (dequeIterator != mEnvelopeContainer.end())
        {
            (*dequeIterator)->setHoldTime (input);
            ++dequeIterator;
        }
    }
}

void EnvelopeVoiceManager::setReleaseTime (double input)
{
    mReleaseTime = input;

    if (mEnvelopeContainer.empty() == false)
    {
        std::deque< ScopedPointer<AHREnvelopeGenerator> >::iterator dequeIterator = mEnvelopeContainer.begin();
        
        while (dequeIterator != mEnvelopeContainer.end())
        {
            (*dequeIterator)->setReleaseTime (input);
            ++dequeIterator;
        }
    }
}

void EnvelopeVoiceManager::setVelocitySensitivity (double input)
{
    mVelocitySensitivity = input;

    if (mEnvelopeContainer.empty() == false)
    {
        std::deque< ScopedPointer<AHREnvelopeGenerator> >::iterator dequeIterator = mEnvelopeContainer.begin();
        
        while (dequeIterator != mEnvelopeContainer.end())
        {
            (*dequeIterator)->setVelocitySensitivity (input);
            ++dequeIterator;
        }
    }
}

void EnvelopeVoiceManager::reset (double inputSampleRate)
{
    mSampleRate = inputSampleRate;
    
    if (mEnvelopeContainer.empty() == false)
    {
        std::deque< ScopedPointer<AHREnvelopeGenerator> >::iterator dequeIterator = mEnvelopeContainer.begin();
        
        while (dequeIterator != mEnvelopeContainer.end())
        {
            (*dequeIterator)->setSampleRate (inputSampleRate);
            ++dequeIterator;
        }
    }
}
