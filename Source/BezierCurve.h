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

    double getOutput (double inputXValue);

    inline void setPointA (double inputXValue, double inputYValue) { mPointA.xValue = inputXValue;
                                                                     mPointA.yValue = inputYValue; };

    inline void setPointB (double inputXValue, double inputYValue) { mPointB.xValue = inputXValue;
                                                                     mPointB.yValue = inputYValue; };

    inline void setPointC (double inputXValue, double inputYValue) { mPointC.xValue = inputXValue;
                                                                     mPointC.yValue = inputYValue; };

    inline void setPointD (double inputXValue, double inputYValue) { mPointD.xValue = inputXValue;
                                                                     mPointD.yValue = inputYValue; };

private:

    BezierPoint getPointOnCurve (double timeIndex);

    BezierPoint mPointA;
    BezierPoint mPointB;
    BezierPoint mPointC;
    BezierPoint mPointD;

};

#endif // BEZIERCURVE_H_INCLUDED
