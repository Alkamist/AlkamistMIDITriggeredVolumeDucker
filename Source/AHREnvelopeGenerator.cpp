#include <cmath>

#include "AHREnvelopeGenerator.h"

AHREnvelopeGenerator::AHREnvelopeGenerator()
    : mHoldLevel (0.0f),
      mAttackTime (0.1f),
      mHoldTime (0.1f),
      mReleaseTime (0.1f),
      mVelocitySensitivity (1.0f),
      mEnvelopeOutput (1.0f),
      mSampleRate (44100),
      mCurrentStageSampleIndex (0),
      mNextStageSampleIndex (0),
      mCurrentStage (3),
      mMultiplier (1.0f),
      mScaleFactor (1.0f),
      mEnvelopeSampleIndex (0)
{}

void AHREnvelopeGenerator::restartEnvelope()
{
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
    double adjustedVelocity = invertedVelocity * mVelocitySensitivity * 0.01f;

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

void AHREnvelopeGenerator::processEnvelope()
{
    // Should we enter a stage?
    if (mCurrentStageSampleIndex >= mNextStageSampleIndex)
    {
        double msToSeconds = 0.001f;
        ++mCurrentStage;
        mCurrentStageSampleIndex = 0;

        switch (mCurrentStage)
        {
            default:
                break;

            // Attack
            case 0:
                mNextStageSampleIndex = mAttackTime * msToSeconds * mSampleRate;
                mMultiplier = calculateMultiplier (mEnvelopeOutput, 
                                                   mScaleFactor, 
                                                   mNextStageSampleIndex);
                break;

            // Hold
            case 1:
                mNextStageSampleIndex = mHoldTime * msToSeconds * mSampleRate;
                mEnvelopeOutput = mScaleFactor;
                mMultiplier = 1.0f;
                break;

            // Release
            case 2:
                mNextStageSampleIndex = mReleaseTime * msToSeconds * mSampleRate - 1;
                mMultiplier = calculateMultiplier (mEnvelopeOutput, 
                                                   1.0f, 
                                                   mNextStageSampleIndex);
                break;
        }
    }

    // Has the envelope finished?
    if (mCurrentStage == 3)
    {
        mCurrentStageSampleIndex = -1;
        mNextStageSampleIndex = 0;
        mEnvelopeOutput = 1.0f;
    }
    else
    {
        mEnvelopeOutput *= mMultiplier;
        ++mCurrentStageSampleIndex;
        ++mEnvelopeSampleIndex;
    }
}