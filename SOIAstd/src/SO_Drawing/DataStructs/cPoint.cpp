
#include "fPoint.h"
#include "pxPoint.h"
#include "cPoint.h"

using namespace SO::Drawing;

cPoint::cPoint() : fPoint()
{	
	px = new pxPoint();
}
cPoint::cPoint(float fX, float fY, int pxX, int pxY)
{
	X = fX;
	Y = fY;
	px = new pxPoint(pxX, pxY);
}
cPoint::cPoint(const fPoint &newF, const pxPoint &newPx) : fPoint(newF)
{
	px = new pxPoint(newPx);
}
cPoint::~cPoint()
{
	//delete px;
}

float cPoint::getFX()
{
	return X;
}
float cPoint::getFY()
{
	return Y;
}

pxPoint cPoint::ToPxPoint(const pxPoint &absolutSpaceSize)
{
	pxPoint absolute = fPoint::ToPxPoint(absolutSpaceSize);
	absolute.X += px->X;
	absolute.Y += px->X;
	return absolute;
}