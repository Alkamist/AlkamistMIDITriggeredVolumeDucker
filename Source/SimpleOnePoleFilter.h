/*
  ==============================================================================

    SimpleOnePoleFilter.h
    Created: 3 Aug 2015 3:23:56pm
    Author:  Corey

  ==============================================================================
*/

#ifndef SIMPLEONEPOLEFILTER_H_INCLUDED
#define SIMPLEONEPOLEFILTER_H_INCLUDED

class SimpleOnePoleFilter
{
public:
    SimpleOnePoleFilter(float coefficient);

    float getOutput(float inputValue) const;   
private:
    mutable float mHistory;
    mutable float mCoefficient;
};


#endif  // SIMPLEONEPOLEFILTER_H_INCLUDED
