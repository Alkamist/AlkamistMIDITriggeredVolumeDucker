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
                                const String& parameterName)
    : mParentProcessor (inputProcessor),
      mDefaultValue (defaultParameterValue),
      mValue (defaultParameterValue),
      mName (parameterName),
      mMinimumValue (minimumParameterValue),
      mMaximumValue (maximumParameterValue),
      mNormalizableRange (mMinimumValue, mMaximumValue)
{}

String FloatParameter::getText()
{
    float outputValue = mNormalizableRange.convertFrom0to1 (mValue);
    String outputString (outputValue);

    return outputString;
}

void FloatParameter::setValue (float newValue)                   
{ 
    mValue = newValue;

    mParentProcessor->parameterChange(this);
}

float FloatParameter::getUnNormalizedValue()
{
    float newValue = mNormalizableRange.convertFrom0to1 (mValue);

    return newValue;
}

void FloatParameter::setNormalizedValue (float nonNormalizedValue)
{
    float newValue = mNormalizableRange.convertTo0to1 (nonNormalizedValue);

    this->setValueNotifyingHost (newValue);
}