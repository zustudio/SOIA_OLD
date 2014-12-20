#include "fPoint.h"
#include "fColor.h"
#include "fCanvasObject.h"

using namespace SO::Drawing;

//////////////////////////////////////////////////
// init
fCanvasObject::fCanvasObject(CanvasObjT NewType, const fPoint &NewP1, const fPoint &NewP2, const fColor &NewColor)
{
	Type = NewType;
	P1 = new fPoint(NewP1);
	P2 = new fPoint(NewP2);
	Color = new fColor(NewColor);
}
fCanvasObject::~fCanvasObject()
{
}