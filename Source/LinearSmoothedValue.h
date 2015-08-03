/*
==============================================================================

    LinearSmoothedValue.h
    Created: 3 Aug 2015 10:29:51am
    Author:  Corey

==============================================================================
*/

#ifndef LINEARSMOOTHEDVALUE_H_INCLUDED
#define LINEARSMOOTHEDVALUE_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class LinearSmoothedValue
{
public:
    LinearSmoothedValue(float defaultValue);

    void reset (float sampleRate, float fadeLengthSeconds);
    void setValue (float newValue);
    void processNextValue() const;

    inline float getCurrentValue() const { return mCurrentValue; };

private:
    mutable float mCurrentValue;
    mutable float mTarget;
    mutable float mStep;
    mutable int mCountdown;
    mutable int mStepsToTarget;

    JUCE_DECLARE_NON_COPYABLE (LinearSmoothedValue)
};

#endif  // LINEARSMOOTHEDVALUE_H_INCLUDED
