/*
==============================================================================

    LinearSmoothedValue.cpp
    Created: 3 Aug 2015 10:29:51am
    Author:  Corey

==============================================================================
*/

#include "LinearSmoothedValue.h"

LinearSmoothedValue::LinearSmoothedValue(float defaultValue)
  : mCurrentValue (defaultValue), 
    mTarget (defaultValue), 
    mStep (0), 
    mCountdown (0), 
    mStepsToTarget (0)
{}

void LinearSmoothedValue::reset (float sampleRate, float fadeLengthSeconds)
{
    jassert (sampleRate > 0 && fadeLengthSeconds >= 0);
    mStepsToTarget = (int) std::floor (fadeLengthSeconds * sampleRate);
    mCurrentValue = mTarget;
    mCountdown = 0;
}

void LinearSmoothedValue::setValue (float newValue)
{
    if (mTarget != newValue)
    {
        mTarget = newValue;
        mCountdown = mStepsToTarget;

        if (mCountdown <= 0)
            mCurrentValue = mTarget;
        else
            mStep = (mTarget - mCurrentValue) / (float) mCountdown;
    }
}

void LinearSmoothedValue::processNextValue() const
{
    if (mCountdown <= 0)
    {
        mCurrentValue = mTarget;
        return;
    }

    --mCountdown;
    mCurrentValue += mStep;
}