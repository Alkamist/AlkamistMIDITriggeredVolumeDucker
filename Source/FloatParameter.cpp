/*
  ==============================================================================

    FloatParameter.cpp
    Created: 29 Jul 2015 2:36:34pm
    Author:  Corey

  ==============================================================================
*/

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
      mDefaultValue (defaultParameterValue),
      mValue (defaultParameterValue),
      mName (parameterName),
      mMinimumValue (minimumParameterValue),
      mMaximumValue (maximumParameterValue),
      mNormalizableRange (mMinimumValue, mMaximumValue)
{
    initializeParameterSmoother (inputSampleRate, inputBlockSize);
}

String FloatParameter::getText()
{
    float outputValue = 0.0f;
    String outputString (outputValue);

    return outputString;
}

void FloatParameter::setValue (float newValue)                   
{ 
    mValue.setValue(newValue);

    mParentProcessor->parameterChange(this);
}

float FloatParameter::getUnNormalizedValue()
{
    float newValue = 0.0f;

    return newValue;
}

void FloatParameter::setNormalizedValue (float nonNormalizedValue)
{
    float newValue = mNormalizableRange.convertTo0to1 (nonNormalizedValue);

    this->setValueNotifyingHost (newValue);
}

void FloatParameter::initializeParameterSmoother (float inputSampleRate, int inputBlockSize)
{
    float smoothingTimeInSeconds = (float) inputBlockSize / inputSampleRate;
    this->mValue.reset(inputSampleRate, smoothingTimeInSeconds);
}