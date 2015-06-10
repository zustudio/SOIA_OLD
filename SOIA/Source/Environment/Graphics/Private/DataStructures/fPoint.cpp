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

using namespace Graphics;
using namespace ZABS::Math;

//////////////////////////////////////////////////////////////////////////////////
// init
fPoint::fPoint(float newX, float newY) : Vector2D<float>(newX, newY)
{

}
fPoint::fPoint(const ZABS::Math::Vector2D<float> &equalPoint)
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


