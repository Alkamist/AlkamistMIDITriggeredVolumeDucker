/*
  ==============================================================================

    FloatParameter.h
    Created: 29 Jul 2015 2:36:34pm
    Author:  Corey

  ==============================================================================
*/

#ifndef FLOATPARAMETER_H_INCLUDED
#define FLOATPARAMETER_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "LinearSmoothedValue.h"
#include "SimpleOnePoleFilter.h"

class AlkamistSidechainCompressorAudioProcessor;

class FloatParameter : public AudioProcessorParameter
{
public:
    FloatParameter (AlkamistSidechainCompressorAudioProcessor* inputProcessor, 
                    float defaultParameterValue,
                    float minimumParameterValue,
                    float maximumParameterValue,
                    const String& parameterName,
                    float inputSampleRate,
                    int inputBlockSize);

    inline float getDefaultValue() const override                         { return mDefaultValue; };
    inline String getName (int /*maximumStringLength*/) const override    { return mName; };
    inline String getLabel() const override                               { return String(); };
    inline float getValueForText (const String& text) const override      { return text.getFloatValue(); };
    inline float getValue() const override                                
    { 
        mValue.processNextValue();
        float output = mSimpleOnePoleFilter.getOutput(mValue.getCurrentValue());
        return output;
    };

    inline float getMinimum() { return mMinimumValue; };
    inline float getMaximum() { return mMaximumValue; };

    String getText() override;
    void setValue (float newValue) override; 

    void initializeParameterSmoother (float inputSampleRate, int inputBlockSize);

    float getUnNormalizedValue();
    void setNormalizedValue (float nonNormalizedValue);
private:
    AlkamistSidechainCompressorAudioProcessor* mParentProcessor;
    float mDefaultValue;
    LinearSmoothedValue mValue;
    String mName;

    float mMinimumValue;
    float mMaximumValue;
    float mSampleRate;

    SimpleOnePoleFilter mSimpleOnePoleFilter;

    NormalisableRange<float> mNormalizableRange;
};

#endif  // FLOATPARAMETER_H_INCLUDED
