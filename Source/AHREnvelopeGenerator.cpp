#include <cmath>

#include "AHREnvelopeGenerator.h"

const double msToSeconds = 0.001;

AHREnvelopeGenerator::AHREnvelopeGenerator()
    : mEnvelopeOutput (1.0),
      mStartingLevel (1.0),
      mHoldTime (0.0),
      mEnvelopeIsFinished (false)
{}

void AHREnvelopeGenerator::reset (double inputSampleRate, int inputBlockSize)
{
    mSampleRate = inputSampleRate;
    mBlockSize = inputBlockSize;
}

double AHREnvelopeGenerator::getOutput()                                
{
    return mEnvelopeOutput;
}

void AHREnvelopeGenerator::startEnvelope()
{
    mEnvelopeIsFinished = false;
    mCurrentStageSampleIndex = 0;
    mNextStageSampleIndex = 0;
    mCurrentStage = -1;
}

void AHREnvelopeGenerator::setVelocityScaleFactor (uint8 velocity)
{
    NormalisableRange<double> normalizableRangeForHoldLevel (0.0, -30.0);
    double normalizedHoldLevel = normalizableRangeForHoldLevel.convertTo0to1 (mHoldLevel);

    double scaledVelocity = velocity / 127.0;

    double outputScaleFactor = 1.0 - (normalizedHoldLevel * scaledVelocity);

    // This outputs logarithmcally scaled values.
    // Simplified from:
    // std::pow(10.0, (-maxHoldLevel / 20.0) * (adjustedVelocity - 1));
    double logarithmicScaleFactor = std::pow(10.0, 1.5 * (outputScaleFactor - 1));

    mScaleFactor = logarithmicScaleFactor;
}

void AHREnvelopeGenerator::performStateChange()
{
    ++mCurrentStage;
    mCurrentStageSampleIndex = 0;

    switch (mCurrentStage)
    {
    default:
        break;

    // Attack
    case 0:
    {
        mNextStageSampleIndex = int (mAttackTime * msToSeconds * mSampleRate);
        mEnvelopeOutput = std::max (mStartingLevel, mScaleFactor);

        mBezierCurve.setPointA (0.0, 1.0);

        mBezierCurve.setPointB (mNextStageSampleIndex * mAttackTopWeight, 1.0);

        mBezierCurve.setPointC (mNextStageSampleIndex * mAttackBottomWeight, mScaleFactor);

        mBezierCurve.setPointD (mNextStageSampleIndex, mScaleFactor);

        break;
    }

    // Hold
    case 1:
        mNextStageSampleIndex = int (mHoldTime * msToSeconds * mSampleRate);
        mEnvelopeOutput = mScaleFactor;
        break;

    // Release
    case 2:
    {
        mNextStageSampleIndex = int (mReleaseTime * msToSeconds * mSampleRate);

        mBezierCurve.setPointA (0.0, mScaleFactor);
    
        mBezierCurve.setPointB (mNextStageSampleIndex * mReleaseBottomWeight, mScaleFactor);

        mBezierCurve.setPointC (mNextStageSampleIndex * mReleaseTopWeight, 1.0);

        mBezierCurve.setPointD (mNextStageSampleIndex, 1.0);

        break;
    }

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

void AHREnvelopeGenerator::processSample()
{
    if (! mEnvelopeIsFinished)
    {
        // Should we enter a stage?
        if (mCurrentStageSampleIndex >= mNextStageSampleIndex)
        {
            performStateChange();
        }

        switch (mCurrentStage)
        {
        default:
            mEnvelopeOutput = 1.0;
            break;

        // Attack
        case 0:
            mEnvelopeOutput = mBezierCurve.getOutput (mCurrentStageSampleIndex);
            break;

        // Hold
        case 1:
            mEnvelopeOutput = mScaleFactor;
            break;

        // Release
        case 2:
            mEnvelopeOutput = mBezierCurve.getOutput (mCurrentStageSampleIndex);
            break;
        }

        ++mCurrentStageSampleIndex;
    }
}