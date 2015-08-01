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
    float scaledVelocity = (velocity - 1) / 126.0;

    // Invert the floating point velocity so it goes
    // from 1 to 0.
    float invertedVelocity = 1 - scaledVelocity;

    // Scale the velocity by the velocity sensitivity.
    float adjustedVelocity = invertedVelocity * mVelocitySensitivity;

    // Convert the floating point velocity to logarithmic
    // scale.
    float logarithmicVelocity = std::pow(10.0f, (-mHoldLevel / 20.0f) * (adjustedVelocity - 1));

    // Set the output.
    mScaleFactor = logarithmicVelocity;
}

float AHREnvelopeGenerator::calculateMultiplier(float startLevel, 
                                                float endLevel, 
                                                int lengthInSamples)
{
    float minimumValue = 0.0001f;

    if (startLevel < minimumValue)
    {
        startLevel = minimumValue;
    }
    if (endLevel < minimumValue)
    {
        endLevel = minimumValue;
    }

    return 1.0 + (std::log(endLevel / startLevel)) / (lengthInSamples);
}

void AHREnvelopeGenerator::processEnvelope()
{
    // Should we enter a stage?
    if (mCurrentStageSampleIndex >= mNextStageSampleIndex)
    {
        ++mCurrentStage;
        mCurrentStageSampleIndex = 0;

        switch (mCurrentStage)
        {
            default:
                break;

            // Attack
            case 0:
                mNextStageSampleIndex = mAttackTime * 0.001f * mSampleRate;
                mMultiplier = calculateMultiplier (mEnvelopeOutput, 
                                                   mScaleFactor, 
                                                   mNextStageSampleIndex);
                break;

            // Hold
            case 1:
                mNextStageSampleIndex = mHoldTime * 0.001f * mSampleRate;
                mEnvelopeOutput = mScaleFactor;
                mMultiplier = 1.0f;
                break;

            // Release
            case 2:
                mNextStageSampleIndex = mReleaseTime * 0.001f * mSampleRate - 1;
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