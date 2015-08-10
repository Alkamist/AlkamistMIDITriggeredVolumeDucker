#include <cmath>

#include "AHREnvelopeGenerator.h"

AHREnvelopeGenerator::AHREnvelopeGenerator()
    : mHoldLevel (0.0),
      mAttackTime (0.1),
      mHoldTime (0.1),
      mReleaseTime (0.1),
      mVelocitySensitivity (1.0),
      mEnvelopeOutput (1.0),
      mSampleRate (44100),
      mCurrentStageSampleIndex (0),
      mNextStageSampleIndex (0),
      mCurrentStage (-1),
      mMultiplier (1.0),
      mScaleFactor (1.0),
      mEnvelopeSampleIndex (0),
      mEnvelopeIsFinished (false)
{}

void AHREnvelopeGenerator::startEnvelope()
{
    mEnvelopeIsFinished = false;
    mEnvelopeSampleIndex = 0;
    mCurrentStageSampleIndex = 0;
    mNextStageSampleIndex = 0;
    mCurrentStage = -1;
}

void AHREnvelopeGenerator::setVelocityScaleFactor (uint8 velocity)
{
    // Cut off the note-off (velocity 0) and scale
    // to floating point.
    double scaledVelocity = (velocity - 1) / 126.0;

    // Invert the floating point velocity so it goes
    // from 1 to 0.
    double invertedVelocity = 1 - scaledVelocity;

    // Scale the velocity by the velocity sensitivity.
    double adjustedVelocity = invertedVelocity * mVelocitySensitivity * 0.01;

    // Convert the floating point velocity to logarithmic
    // scale.
    double logarithmicVelocity = std::pow(10.0, (-mHoldLevel / 20.0) * (adjustedVelocity - 1));

    // Set the output.
    mScaleFactor = logarithmicVelocity;
}

double AHREnvelopeGenerator::calculateMultiplier(double startLevel, 
                                                double endLevel, 
                                                int lengthInSamples)
{
    return 1.0 + (std::log(endLevel / startLevel)) / (lengthInSamples);
}

void AHREnvelopeGenerator::performStateChange()
{
    double msToSeconds = 0.001;
    ++mCurrentStage;
    mCurrentStageSampleIndex = 0;

    switch (mCurrentStage)
    {
    default:
        break;

    // Attack
    case 0:
        mNextStageSampleIndex = (int) std::floor(mAttackTime * msToSeconds * mSampleRate);
        mMultiplier = calculateMultiplier (mEnvelopeOutput, 
                                           mScaleFactor, 
                                           mNextStageSampleIndex);
        break;

    // Hold
    case 1:
        mNextStageSampleIndex = (int) std::floor(mHoldTime * msToSeconds * mSampleRate);
        mEnvelopeOutput = mScaleFactor;
        mMultiplier = 1.0;
        break;

    // Release
    case 2:
        mNextStageSampleIndex = (int) std::floor(mReleaseTime * msToSeconds * mSampleRate - 1);
        mMultiplier = calculateMultiplier (mEnvelopeOutput, 
                                           1.0, 
                                           mNextStageSampleIndex);
        break;

    // Finished
    case 3:
        mEnvelopeIsFinished = true;
        mCurrentStage = -1;
        mCurrentStageSampleIndex = 0;
        mNextStageSampleIndex = 0;
        mEnvelopeOutput = 1.0;
        break;
    }
}

void AHREnvelopeGenerator::processPerSample()
{
    if (!mEnvelopeIsFinished)
    {
        // Should we enter a stage?
        if (mCurrentStageSampleIndex >= mNextStageSampleIndex)
        {
            performStateChange();
        }

        mEnvelopeOutput *= mMultiplier;
        ++mCurrentStageSampleIndex;
        ++mEnvelopeSampleIndex;
    }
}