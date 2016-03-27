#include "QuadraticBezierCurve.h"

QuadraticBezierCurve::QuadraticBezierCurve()
{}

BezierPoint LinearInterpolate (const BezierPoint& pointA, const BezierPoint& pointB, const double inputXValue)
{
    BezierPoint outputPoint;

    outputPoint.xValue = inputXValue;

    // This is the algebra that combines the two equations.
    //(outputPoint.xValue - pointA.xValue) / (pointB.xValue - pointA.xValue) = timeIndex;
    //(outputPoint.yValue - pointA.yValue) / (pointB.yValue - pointA.yValue) = timeIndex;
    //(outputPoint.xValue - pointA.xValue) / (pointB.xValue - pointA.xValue) = (outputPoint.yValue - pointA.yValue) / (pointB.yValue - pointA.yValue);

    outputPoint.yValue = ( (outputPoint.xValue - pointA.xValue) * (pointB.yValue - pointA.yValue) / (pointB.xValue - pointA.xValue) )
                         + pointA.yValue;

    return outputPoint;
}

// This is what the interpolation would be like if we needed time to be a factor.
/*BezierPoint LinearInterpolate (const BezierPoint& pointA, const BezierPoint& pointB, const double timeIndex)
{
    BezierPoint outputPoint;

    outputPoint.xValue = pointA.xValue + (pointB.xValue - pointA.xValue) * timeIndex;
    outputPoint.yValue = pointA.yValue + (pointB.yValue - pointA.yValue) * timeIndex;

    return outputPoint;
}*/

double QuadraticBezierCurve::getOutput (int inputSampleNumber)
{
    BezierPoint pointAB;
    BezierPoint pointBC;
    BezierPoint outputPoint;

    pointAB = LinearInterpolate (mPoint1, mPoint2, inputSampleNumber * mPoint2.xValue / mPoint3.xValue);
    pointBC = LinearInterpolate (mPoint2, mPoint3, mPoint2.xValue + inputSampleNumber * (mPoint3.xValue - mPoint2.xValue) / mPoint3.xValue);

    outputPoint = LinearInterpolate (pointAB, pointBC, inputSampleNumber);

    return outputPoint.yValue;
}