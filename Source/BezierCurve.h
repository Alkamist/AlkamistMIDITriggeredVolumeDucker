#ifndef BEZIERCURVE_H_INCLUDED
#define BEZIERCURVE_H_INCLUDED

struct BezierPoint
{
    double xValue;
    double yValue;
};

class BezierCurve
{
public:

    BezierCurve();

    double getOutput (int inputSampleNumber);

    inline void setPoint1 (double inputXValue, double inputYValue) { mPoint1.xValue = inputXValue;
                                                                     mPoint1.yValue = inputYValue; };

    inline void setPoint2 (double inputXValue, double inputYValue) { mPoint2.xValue = inputXValue;
                                                                     mPoint2.yValue = inputYValue; };

    inline void setPoint3 (double inputXValue, double inputYValue) { mPoint3.xValue = inputXValue;
                                                                     mPoint3.yValue = inputYValue; };

private:

    BezierPoint mPoint1;
    BezierPoint mPoint2;
    BezierPoint mPoint3;

};

#endif // BEZIERCURVE_H_INCLUDED
