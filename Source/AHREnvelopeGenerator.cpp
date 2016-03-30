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
    // This outputs linearly scaled values.
    //return mEnvelopeOutput;

    // This outputs logarithmcally scaled values.
    // Simplified from:
    // std::pow(10.0, (-mHoldLevel / 20.0) * (adjustedVelocity - 1));
    return std::pow(10.0, 3.0 * (mEnvelopeOutput - 1));
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
    // Establish a normalized hold level to work with.
    NormalisableRange<double> normalizableRangeForHoldLevel (0.0, -60.0);
    double normalizedHoldLevel = normalizableRangeForHoldLevel.convertTo0to1 (mHoldLevel);

    // Establish how the velocity threshold should change
    // based on the hold level.
    NormalisableRange<double> holdLevelToVelocityThreshold (50, 1.0, 1.0, 1.3);
    int holdLevelAsVelocityThreshold = int (holdLevelToVelocityThreshold.convertFrom0to1 (normalizedHoldLevel));

    // Set the velocity threshold and cut values below it off.
    int velocityThreshold = holdLevelAsVelocityThreshold - 1;
    if (velocity < velocityThreshold) { velocity = velocityThreshold; }

    // Re-scale the velocity based on the threshold.
    double scaledVelocity = (velocity - velocityThreshold) / (127.0 - velocityThreshold);

    // Establish how the velocity values should be skewed
    // based on the hold level.
    NormalisableRange<double> normalizableRangeForVelocitySkew (0.90, 0.25, 0.001, 3.0);
    double holdLevelAsVelocitySkew = normalizableRangeForVelocitySkew.convertFrom0to1 (normalizedHoldLevel);

    NormalisableRange<double> normalizableRangeForSkewedVelocity (0.0, 1.0, 0.007874, holdLevelAsVelocitySkew);
    double scaledVelocityAsSkewedVelocity = normalizableRangeForSkewedVelocity.convertFrom0to1 (scaledVelocity);

    // Set the output.
    double outputScaleFactor = 1.0 - (normalizedHoldLevel * scaledVelocityAsSkewedVelocity);
    mScaleFactor = outputScaleFactor;
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

        // Point B changes position based on the scale factor.
        // This changes the shape of the curve.
        NormalisableRange<double> pointBScaleFactor (0.99, 0.25, 0.001, 0.5);
        mBezierCurve.setPointB (mNextStageSampleIndex * pointBScaleFactor.convertFrom0to1 (mScaleFactor), 1.0);

        // Point C changes position based on the scale factor.
        // This changes the shape of the curve.
        NormalisableRange<double> pointCScaleFactor (0.95, 0.85);
        mBezierCurve.setPointC (mNextStageSampleIndex * pointCScaleFactor.convertFrom0to1 (mScaleFactor), mScaleFactor);

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
    
        // Point B changes position based on the scale factor.
        // This changes the shape of the curve.
        NormalisableRange<double> pointBScaleFactor (0.05, 0.15);
        mBezierCurve.setPointB (mNextStageSampleIndex * pointBScaleFactor.convertFrom0to1 (mScaleFactor), mScaleFactor);

        // Point C changes position based on the scale factor.
        // This changes the shape of the curve.
        NormalisableRange<double> pointCScaleFactor (0.01, 0.75, 0.001, 0.5);
        mBezierCurve.setPointC (mNextStageSampleIndex * pointCScaleFactor.convertFrom0to1 (mScaleFactor), 1.0);

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