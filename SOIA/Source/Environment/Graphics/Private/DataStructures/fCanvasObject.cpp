
#include "Definitions.h"

#include "fPoint.h"
#include "fColor.h"
#include "fCanvasObject.h"

using namespace Graphics;

//////////////////////////////////////////////////
// init
fCanvasObject::fCanvasObject(CanvasObjT NewType, const fPoint &NewP1, const fPoint &NewP2, const fColor &NewColor, void *NewContent)
{
	Type = NewType;
	P1 = new fPoint(NewP1);
	P2 = new fPoint(NewP2);
	Color = new fColor(NewColor);
	Content = NewContent;
	CustomParts = std::vector<fCanvasObject*>();
}
fCanvasObject::~fCanvasObject()
{
}

//////////////////////////////////////////////////
// custom parts pseudo-interface
std::vector<fCanvasObject*>* fCanvasObject::GetCustomParts()
{
	return &CustomParts;
}
void fCanvasObject::Highlight(bool bEnable)
{
	static fColor* backup;

	if (bEnable)
	{
		backup = Color;
		Color = new fColor(1, 0.2, 0.2);
	}
	else
	{
		delete Color;
		Color = backup;
	}
}
