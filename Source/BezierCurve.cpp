#include "BezierCurve.h"

BezierCurve::BezierCurve()
{}

BezierPoint BezierCurve::LinearInterpolate (const BezierPoint& pointA, const BezierPoint& pointB, const double inputXValue)
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

double BezierCurve::getOutput (int inputSampleNumber)
{
    BezierPoint pointAB;
    BezierPoint pointBC;
    BezierPoint pointCD;
    BezierPoint pointABBC;
    BezierPoint pointBCCD;
    BezierPoint outputPoint;

    double totalNumberOfSamples = mPointD.xValue;

    pointAB = LinearInterpolate (mPointA, mPointB, inputSampleNumber * mPointB.xValue / totalNumberOfSamples);
    pointBC = LinearInterpolate (mPointB, mPointC, mPointB.xValue + inputSampleNumber * (mPointC.xValue - mPointB.xValue) / totalNumberOfSamples);
    pointCD = LinearInterpolate (mPointC, mPointD, mPointC.xValue + inputSampleNumber * (mPointD.xValue - mPointC.xValue) / totalNumberOfSamples);
    pointABBC = LinearInterpolate (pointAB, pointBC, inputSampleNumber * (mPointC.xValue - mPointA.xValue) / totalNumberOfSamples);
    pointBCCD = LinearInterpolate (pointBC, pointCD, mPointB.xValue + inputSampleNumber * (mPointD.xValue - mPointB.xValue) / totalNumberOfSamples);

    outputPoint = LinearInterpolate (pointABBC, pointBCCD, inputSampleNumber);

    return outputPoint.yValue;
}