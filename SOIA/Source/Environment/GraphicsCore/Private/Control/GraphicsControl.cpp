
#include "Definitions.h"

#include "GraphicsControl.h"
using namespace Environment;

#include "ControlWindow.h"

GraphicsControl::GraphicsControl(MBoundaries * InBoundaries, pxMargins InMargins)
	: MBoundaries(InBoundaries, InMargins),
	Border(
		this,
		pxMargins(0,0,0,0),
		fColor(1, 1, 1),
		[this]() {return GeometryObject::MakeRectangle(pxPoint(0, 0), GetSize().ToPoint()); })
{
	GetWindow()->CommonFilledGeometryLayer.AddObject(&Border);
}

void GraphicsControl::Event_KeyChanged(EventInfo_KeyChanged const & InInfo)
{
}

void GraphicsControl::Event_SelectionChanged(EventInfo_SelectionChanged const & InInfo)
{
	if (InInfo == ESelectionStatus::Selected)
	{
		Border.Color = fColor(1, 1, 1);
		Border.RequestUpdate();
		bSelected = true;
	}
	else
	{
		Border.Color = fColor(0.8, 0.8, 0.8);
		Border.RequestUpdate();
		bSelected = false;
	}
}

bool GraphicsControl::IsSelected()
{
	return bSelected;
}

ControlWindow* GraphicsControl::GetWindow()
{
	return dynamic_cast<ControlWindow*>(GetTopBoundaries());
}
