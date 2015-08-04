#include "LinearlySmoothedFloat.h"

LinearlySmoothedFloat::LinearlySmoothedFloat(double defaultValue)
  : mCurrentValue (defaultValue),
    mTarget (defaultValue),
    mStep (0),
    mCountdown (0),
    mStepsToTarget (0)
{}

void LinearlySmoothedFloat::reset (double sampleRate, double fadeLengthSeconds)
{
    jassert (sampleRate > 0 && fadeLengthSeconds >= 0);
    mStepsToTarget = (int) std::floor (fadeLengthSeconds * sampleRate);
    mCurrentValue = mTarget;
    mCountdown = 0;
}

void LinearlySmoothedFloat::setValue (double inputValue)
{
    if (mTarget != inputValue)
    {
        mTarget = inputValue;
        mCountdown = mStepsToTarget;

        if (mCountdown <= 0)
            mCurrentValue = mTarget;
        else
            mStep = (mTarget - mCurrentValue) / (double) mCountdown;
    }
}

void LinearlySmoothedFloat::processPerSample()
{
    if (mCountdown <= 0)
    {
        mCurrentValue = mTarget;
    }
    else
    {
        --mCountdown;
        mCurrentValue += mStep;
    }

}