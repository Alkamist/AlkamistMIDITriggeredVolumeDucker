#ifndef QUADRATICBEZIERCURVE_H_INCLUDED
#define QUADRATICBEZIERCURVE_H_INCLUDED

struct BezierPoint
{
    double xValue;
    double yValue;
};

class QuadraticBezierCurve
{
public:

    QuadraticBezierCurve();

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

#endif  // QUADRATICBEZIERCURVE_H_INCLUDED
