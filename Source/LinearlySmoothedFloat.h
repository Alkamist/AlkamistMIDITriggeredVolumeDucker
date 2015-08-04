#ifndef LINEARLYSMOOTHEDFLOAT_H_INCLUDED
#define LINEARLYSMOOTHEDFLOAT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class LinearlySmoothedFloat
{
public:
    LinearlySmoothedFloat(double defaultValue);

    void reset (double sampleRate, double fadeLengthSeconds);
    void processPerSample();

    // Getters
    inline double getCurrentValue() const { return mCurrentValue; };

    // Setters
    void setValue (double newValue);
private:
    mutable double mCurrentValue;
    mutable double mTarget;
    mutable double mStep;
    mutable int mCountdown;
    mutable int mStepsToTarget;

    JUCE_DECLARE_NON_COPYABLE (LinearlySmoothedFloat)
};

#endif  // LINEARSMOOTHEDVALUE_H_INCLUDED
