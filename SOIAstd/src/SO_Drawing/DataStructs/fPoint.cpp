/*
 * fPoint.cpp
 *
 *  Created on: Dec 6, 2014
 *      Author: mxu
 */

#include "Vector2D.h"
#include "pxPoint.h"
#include "fPoint.h"

using namespace SO::Drawing;
using namespace ZABS::Math;

fPoint::fPoint() : Vector2D<float>()
{

}
fPoint::fPoint(float newX, float newY) : Vector2D<float>(newX, newY)
{

}
fPoint::fPoint(const fPoint &equalPoint) : Vector2D<float>(equalPoint)
{

}
//// conversion
pxPoint fPoint::ToPxPoint(pxPoint &absolutSpaceSize)
{
	int newX = int(X * absolutSpaceSize.X);
	int newY = int(Y * absolutSpaceSize.Y);
	pxPoint px = pxPoint(newX, newY);
	return px;
}


