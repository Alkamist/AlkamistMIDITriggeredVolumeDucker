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
    // Set the velocity threshold and cut values below it off.
    int velocityThreshold = int (mVelocityThreshold) - 1;
    if (velocity < velocityThreshold) { velocity = velocityThreshold; }

    // Re-scale the velocity based on the threshold.
    double scaledVelocity = (velocity - velocityThreshold) / (127.0 - velocityThreshold);

    // Skew the velocity based on the skew parameter, 
    // then factor in the hold level.
    NormalisableRange<double> skewedVelocity (0.0, 1.0, 0.007874, mVelocitySkew);
    NormalisableRange<double> normalizedHoldLevel (0.0, -60.0);
    double outputScaleFactor = 1.0 - (normalizedHoldLevel.convertTo0to1 (mHoldLevel) * skewedVelocity.convertFrom0to1 (scaledVelocity));

    // Set the output.
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

        // Point B changes position based on the scale factor;
        // this changes the shape of the curve.
        NormalisableRange<double> pointBScaleFactor (0.5, 0.3);
        mBezierCurve.setPointB (mNextStageSampleIndex * pointBScaleFactor.convertFrom0to1 (mScaleFactor), 1.0);

        mBezierCurve.setPointC (0.9 * mNextStageSampleIndex, mScaleFactor);

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
    
        mBezierCurve.setPointB (mNextStageSampleIndex * 0.1, mScaleFactor);

        // Point C changes position based on the scale factor
        // which changes the shape of the curve.
        NormalisableRange<double> pointCScaleFactor (0.1, 0.5);
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