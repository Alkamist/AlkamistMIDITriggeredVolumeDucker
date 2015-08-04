#include "PluginProcessor.h"

#include "FloatParameter.h"

FloatParameter::FloatParameter (AlkamistSidechainCompressorAudioProcessor* inputProcessor,
                                float defaultParameterValue,
                                float minimumParameterValue,
                                float maximumParameterValue,
                                const String& parameterName,
                                float inputSampleRate,
                                int inputBlockSize)
    : mParentProcessor (inputProcessor),
      mUnSmoothedParameterValue (defaultParameterValue),
      mDefaultValue (defaultParameterValue),
      mMinimumValue (minimumParameterValue),
      mMaximumValue (maximumParameterValue),
      mName (parameterName),
      mNormalizableRange (mMinimumValue, mMaximumValue),
      mLinearlySmoothedFloat (defaultParameterValue)
{
    reset (inputSampleRate, inputBlockSize);
}

String FloatParameter::getText()
{
    float currentValue = mLinearlySmoothedFloat.getCurrentValue();

    float unNormalizedValue = mNormalizableRange.convertFrom0to1 (currentValue);
    String outputString (unNormalizedValue);

    return outputString;
}

void FloatParameter::setValue (float inputValue)
{
    mLinearlySmoothedFloat.setValue (inputValue);

    mUnSmoothedParameterValue = inputValue;

    mParentProcessor->parameterChange (this);
}

float FloatParameter::getUnNormalizedValue()
{
    float currentValue = mLinearlySmoothedFloat.getCurrentValue();

    float unNormalizedValue = mNormalizableRange.convertFrom0to1 (currentValue);

    return unNormalizedValue;
}

float FloatParameter::getUnNormalizedUnSmoothedValue()
{
    float currentValue = mUnSmoothedParameterValue;

    float unNormalizedValue = mNormalizableRange.convertFrom0to1 (currentValue);

    return unNormalizedValue;
}

void FloatParameter::setNormalizedValue (float nonNormalizedValue)
{
    float newValue = mNormalizableRange.convertTo0to1 (nonNormalizedValue);

    this->setValueNotifyingHost (newValue);
}

void FloatParameter::processPerSample()
{
    mLinearlySmoothedFloat.processPerSample();
}

void FloatParameter::reset (float inputSampleRate, int inputBlockSize)
{
    // Linear Parameter Ramp
    float smoothingTimeInSeconds = (float) inputBlockSize / inputSampleRate;
    this->mLinearlySmoothedFloat.reset (inputSampleRate, smoothingTimeInSeconds);
}