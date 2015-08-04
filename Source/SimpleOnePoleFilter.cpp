/*
  ==============================================================================

    SimpleOnePoleFilter.cpp
    Created: 3 Aug 2015 3:23:56pm
    Author:  Corey

  ==============================================================================
*/

#include <cmath>

#include "SimpleOnePoleFilter.h"

SimpleOnePoleFilter::SimpleOnePoleFilter(double inputCutoffFrequency) 
  : mCoefficient (0.0),
    mHistory (0.0),
    mCutoffFrequency (inputCutoffFrequency)
{}

const double SimpleOnePoleFilter::kPI (3.141592653589793);

double SimpleOnePoleFilter::getOutput(double inputValue) const
{
    double result = inputValue + mCoefficient * (mHistory - inputValue);
    mHistory = result;
    return result;
}

void SimpleOnePoleFilter::reset(double inputSampleRate)
{
    mCoefficient = std::exp(-2.0 * kPI * mCutoffFrequency/inputSampleRate);
}