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

class AlkamistSidechainCompressorAudioProcessor;

class FloatParameter : public AudioProcessorParameter
{
public:
    FloatParameter (AlkamistSidechainCompressorAudioProcessor* inputProcessor, 
                    float defaultParameterValue,
                    float minimumParameterValue,
                    float maximumParameterValue,
                    const String& parameterName);

    inline float getDefaultValue() const override                         { return mDefaultValue; };
    inline String getName (int /*maximumStringLength*/) const override    { return mName; };
    inline String getLabel() const override                               { return String(); };
    inline float getValueForText (const String& text) const override      { return text.getFloatValue(); };
    inline float getValue() const override                                { return mValue; };

    inline float getMinimum() { return mMinimumValue; };
    inline float getMaximum() { return mMaximumValue; };

    String getText() override;
    void setValue (float newValue) override; 

    float getUnNormalizedValue();
    void setNormalizedValue (float nonNormalizedValue);
private:
    AlkamistSidechainCompressorAudioProcessor* mParentProcessor;
    float mDefaultValue;
    float mValue;
    String mName;

    float mMinimumValue;
    float mMaximumValue;

    NormalisableRange<float> mNormalizableRange;
};

#endif  // FLOATPARAMETER_H_INCLUDED
