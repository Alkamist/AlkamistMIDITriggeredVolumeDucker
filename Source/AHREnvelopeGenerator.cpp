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
    //return std::pow(10.0, (-mHoldLevel / 20.0) * (mEnvelopeOutput - 1));
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
    double scaledVelocity = (velocity - 1) / 126.0;

    // Invert the floating point velocity so it goes
    // from 1 to 0.
    double invertedVelocity = 1 - scaledVelocity;

    // Scale the velocity by the velocity sensitivity.
    double adjustedVelocity = invertedVelocity * mVelocitySensitivity * 0.01;

    // Convert the floating point velocity to logarithmic
    // scale.
    //double logarithmicVelocity = std::pow(10.0, (-mHoldLevel / 20.0) * (adjustedVelocity - 1));

    // Set the output.
    mScaleFactor = adjustedVelocity;
}

/*
double AHREnvelopeGenerator::calculateMultiplier (double startLevel, 
                                                  double endLevel, 
                                                  unsigned int lengthInSamples)
{
    return 1.0 + (std::log(endLevel / startLevel)) / (lengthInSamples);
}
*/

/*double AHREnvelopeGenerator::calculateMultiplier (double startLevel, 
                                                  double endLevel, 
                                                  unsigned int lengthInSamples)
{
    if (startLevel > endLevel)
    {
        return 1.0 / (1.0 + (std::log(startLevel / endLevel)) / (lengthInSamples));
    }
    else
    {
        return 1.0 + (std::log(endLevel / startLevel)) / (lengthInSamples);
    }
}*/

double AHREnvelopeGenerator::calculateLinearAdder (double startLevel, 
                                                   double endLevel, 
                                                   unsigned int lengthInSamples)
{
    return (endLevel - startLevel) / lengthInSamples;
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
        mNextStageSampleIndex = int (mAttackTime * msToSeconds * mSampleRate);
        mEnvelopeOutput = std::max (mStartingLevel, mScaleFactor);
        mAdder = calculateLinearAdder (mEnvelopeOutput, 
                                       mScaleFactor, 
                                       mNextStageSampleIndex);
        break;

    // Hold
    case 1:
        mNextStageSampleIndex = int (mHoldTime * msToSeconds * mSampleRate);
        mEnvelopeOutput = mScaleFactor;
        mAdder = 0.0;
        break;

    // Release
    case 2:
        mNextStageSampleIndex = int (mReleaseTime * msToSeconds * mSampleRate);

        mBezierCurve.setPoint1 (0.0, mScaleFactor);

        mBezierCurve.setPoint2 (mNextStageSampleIndex / 8, mScaleFactor + ((1.0 - mScaleFactor) / 1.0));

        mBezierCurve.setPoint3 (mNextStageSampleIndex, 1.0);

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
            mEnvelopeOutput += mAdder;
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