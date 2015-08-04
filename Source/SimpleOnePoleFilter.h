#ifndef SIMPLEONEPOLEFILTER_H_INCLUDED
#define SIMPLEONEPOLEFILTER_H_INCLUDED

class SimpleOnePoleFilter
{
public:

    SimpleOnePoleFilter(double inputCutoffFrequency);

    double getOutput(double inputValue) const;
    void reset(double inputSampleRate);

private:

    mutable double mHistory;
    mutable double mCoefficient;
    mutable double mCutoffFrequency;

    static const double kPI;

};


#endif  // SIMPLEONEPOLEFILTER_H_INCLUDED
