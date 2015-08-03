/*
  ==============================================================================

    SimpleOnePoleFilter.cpp
    Created: 3 Aug 2015 3:23:56pm
    Author:  Corey

  ==============================================================================
*/

#include "SimpleOnePoleFilter.h"

SimpleOnePoleFilter::SimpleOnePoleFilter(float coefficient) 
  : mCoefficient(coefficient),
    mHistory (0.0f)
{}

float SimpleOnePoleFilter::getOutput(float inputValue) const
{
    float result = inputValue + mCoefficient * (mHistory - inputValue);
    mHistory = result;
    return result;
}
