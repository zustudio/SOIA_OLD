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
fPoint::fPoint(const ZABS::Math::Vector2D<float> &equalPoint)
{
	X = equalPoint.X; Y = equalPoint.Y;
	//fPoint(equalPoint.X, equalPoint.Y);
}
//// conversion
pxPoint fPoint::ToPxPoint(const pxPoint &absolutSpaceSize)
{
	int newX = int(X * absolutSpaceSize.X);
	int newY = int(Y * absolutSpaceSize.Y);
	pxPoint px = pxPoint(newX, newY);
	return px;
}


