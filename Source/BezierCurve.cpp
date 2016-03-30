#include <cmath>

#include "BezierCurve.h"

BezierCurve::BezierCurve()
{}

BezierPoint LinearInterpolate (const BezierPoint& pointA, const BezierPoint& pointB, const double timeIndex)
{
    BezierPoint outputPoint;

    outputPoint.xValue = pointA.xValue + (pointB.xValue - pointA.xValue) * timeIndex;
    outputPoint.yValue = pointA.yValue + (pointB.yValue - pointA.yValue) * timeIndex;

    return outputPoint;
}

BezierPoint BezierCurve::getPointOnCurve (double timeIndex)
{
    BezierPoint pointAB;
    BezierPoint pointBC;
    BezierPoint pointCD;
    BezierPoint pointABBC;
    BezierPoint pointBCCD;
    BezierPoint outputPoint;

    pointAB = LinearInterpolate (mPointA, mPointB, timeIndex);
    pointBC = LinearInterpolate (mPointB, mPointC, timeIndex);
    pointCD = LinearInterpolate (mPointC, mPointD, timeIndex);
    pointABBC = LinearInterpolate (pointAB, pointBC, timeIndex);
    pointBCCD = LinearInterpolate (pointBC, pointCD, timeIndex);

    outputPoint = LinearInterpolate (pointABBC, pointBCCD, timeIndex);

    return outputPoint;
}

// This is a binary search algorithm that we
// need to use to find the Y value that 
// corresponds with our given X value.
// inputXValue is the target value here.
// This function only works if the Bezier curve
// does not have multiple Y values for any
// given X value, so make sure that the
// control points of the Bezier curve stay
// inside the bounds of the end points.
double BezierCurve::getOutput (double inputXValue)
{
    double totalNumberOfSamples = mPointD.xValue;
    double xTolerance = 1.0 / totalNumberOfSamples;

    double lowerBound = 0.0;
    double upperBound = 1.0;
    double currentPositionInTime = 0.5;

    double currentXValue = getPointOnCurve (currentPositionInTime).xValue;

    while (std::abs (inputXValue - currentXValue) > xTolerance)
    {
        if (inputXValue > currentXValue)
            lowerBound = currentPositionInTime;
        else
            upperBound = currentPositionInTime;

        currentPositionInTime = (lowerBound + upperBound) * 0.5;
        currentXValue = getPointOnCurve (currentPositionInTime).xValue;
    }

    return getPointOnCurve (currentPositionInTime).yValue;
}