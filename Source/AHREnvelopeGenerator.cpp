#include <cmath>

#include "AHREnvelopeGenerator.h"

const double msToSeconds = 0.001;

AHREnvelopeGenerator::AHREnvelopeGenerator()
    : mEnvelopeOutput (1.0),
      mStartingLevel (1.0),
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

    // Simplified from:
    // std::pow(10.0, (-mHoldLevel / 20.0) * (adjustedVelocity - 1));
    //return std::pow(10.0, 3.0 * (mEnvelopeOutput - 1));
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
    // Cut off the note-off (velocity 0) and scale
    // to floating point.
    //double scaledVelocity = (velocity - 1) / 126.0;

    int velocityThreshold = 64 - 1;

    if (velocity < velocityThreshold) { velocity = velocityThreshold; }

    double scaledVelocity = (velocity - velocityThreshold) / (127.0 - velocityThreshold);

    NormalisableRange<double> skewedVelocity (0.0, 1.0, 0.007874, 0.5);
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
        NormalisableRange<double> pointBScaleFactor (2.1, 4.0, 0.001, 2.0);
        mBezierCurve.setPointB (mNextStageSampleIndex / pointBScaleFactor.convertFrom0to1 (mScaleFactor), 1.0);

        mBezierCurve.setPointC (31.0 * mNextStageSampleIndex / 32.0, mScaleFactor);

        mBezierCurve.setPointD (mNextStageSampleIndex, mScaleFactor);

        break;
    }

    // Hold
    case 1:
        mNextStageSampleIndex = int (mHoldTime * msToSeconds * mSampleRate);
        mEnvelopeOutput = mScaleFactor;
        mAdder = 0.0;
        break;

    // Release
    case 2:
    {
        mNextStageSampleIndex = int (mReleaseTime * msToSeconds * mSampleRate);

        mBezierCurve.setPointA (0.0, mScaleFactor);

        mBezierCurve.setPointB (mNextStageSampleIndex / 32.0, mScaleFactor);

        // Point C changes position based on the scale factor;
        // this changes the shape of the curve.
        NormalisableRange<double> pointCScaleFactor (8.0, 1.1, 0.001, 2.0);
        mBezierCurve.setPointC (mNextStageSampleIndex / pointCScaleFactor.convertFrom0to1 (mScaleFactor), 1.0);

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