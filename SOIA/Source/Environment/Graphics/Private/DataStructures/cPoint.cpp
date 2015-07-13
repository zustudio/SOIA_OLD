
#include "Definitions.h"

#include "fPoint.h"
#include "pxPoint.h"
#include "cPoint.h"

using namespace Environment;

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

float cPoint::getFX() const
{
	return X;
}
float cPoint::getFY() const
{
	return Y;
}

pxPoint cPoint::ToPxPoint(pxPoint &absolutSpaceSize)
{
	pxPoint absolute = fPoint::ToPxPoint(absolutSpaceSize);
	absolute += (*px);
	return absolute;
}

