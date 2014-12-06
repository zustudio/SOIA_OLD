/*
 * pxPoint.cpp
*/
#include "Vector2D.h"
#include "fPoint.h"
#include "pxPoint.h"

using namespace SO::Drawing;

//// overloaded constructor
pxPoint::pxPoint(int newX, int newY) : Vector2D<int>(newX, newY)
{

}
pxPoint::pxPoint(const pxPoint &equalPoint) : Vector2D<int>(equalPoint)
{

}
pxPoint::pxPoint() : Vector2D<int>()
{

}
