/*
* pxPoint.cpp
*/

#include "Definitions.h"

#include "Vector2D.h"
#include "fPoint.h"
#include "pxPoint.h"

using namespace Environment;

////////////////////////////////////////////////////////////////////////////
// init
pxPoint::pxPoint(int newX, int newY) : Vector2D<int>(newX, newY)
{

}
pxPoint::pxPoint(const Vector2D<int> &equalVector2D)
{
	X = equalVector2D.X;
	Y = equalVector2D.Y;
}
