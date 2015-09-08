
#include "Definitions.h"

#include "GraphicsControl.h"
using namespace Environment;

#include "ControlWindow.h"

GraphicsControl::GraphicsControl(MBoundaries * InBoundaries, pxMargins InMargins)
	: MBoundaries(InBoundaries, InMargins),
	Border(
		this,
		pxMargins(0,0,0,0),
		fColor(0.95, 0.95, 0.95),
		GeometryObject::MakeRectangle(pxPoint(0,0), GetSize().ToPoint()))
{
	GetWindow()->CommonFilledGeometryLayer.AddObject(Border);
}

ControlWindow* GraphicsControl::GetWindow()
{
	return dynamic_cast<ControlWindow*>(GetTopBoundaries());
}
