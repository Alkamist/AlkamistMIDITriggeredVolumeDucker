#ifndef FLOATPARAMETER_H_INCLUDED
#define FLOATPARAMETER_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "LinearlySmoothedFloat.h"

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

    void processPerSample();
    void reset (float inputSampleRate, int inputBlockSize);

    // Getters
    inline float getDefaultValue() const override                         { return mDefaultValue; };
    inline String getName (int /*maximumStringLength*/) const override    { return mName; };
    inline String getLabel() const override                               { return String(); };
    inline float getValueForText (const String& text) const override      { return text.getFloatValue(); };
    inline float getValue() const override                                { return mLinearlySmoothedFloat.getCurrentValue(); };
    inline float getMinimum() const                                       { return mMinimumValue; };
    inline float getMaximum() const                                       { return mMaximumValue; };
    float getUnNormalizedValue();
    float getUnNormalizedUnSmoothedValue();
    String getText() override;

    // Setters
    void setValue (float newValue) override;
    void setNormalizedValue (float nonNormalizedValue);

private:

    AlkamistSidechainCompressorAudioProcessor* mParentProcessor;

    float mUnSmoothedParameterValue;
    float mDefaultValue;
    float mMinimumValue;
    float mMaximumValue;
    String mName;

    float mSampleRate;

    LinearlySmoothedFloat mLinearlySmoothedFloat;
    NormalisableRange<float> mNormalizableRange;

};

#endif  // FLOATPARAMETER_H_INCLUDED
