/*
 * fPoint.cpp
 *
 *  Created on: Dec 6, 2014
 *      Author: mxu
 */

#include "Definitions.h"

#include "Vector2D.h"
#include "pxPoint.h"
#include "fPoint.h"

using namespace Environment;

//////////////////////////////////////////////////////////////////////////////////
// init
fPoint::fPoint(float newX, float newY) : Vector2D<float>(newX, newY)
{

}
fPoint::fPoint(const Vector2D<float> &equalPoint)
{
	X = equalPoint.X;
	Y = equalPoint.Y;
}
fPoint::~fPoint() {}
//////////////////////////////////////////////////////////////////////////////////
// conversion
pxPoint fPoint::ToPxPoint(pxPoint &absolutSpaceSize)
{
	return pxPoint((*this) * absolutSpaceSize);
}


