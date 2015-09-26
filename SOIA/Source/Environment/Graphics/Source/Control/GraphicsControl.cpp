
#include "Definitions.h"

#include "GraphicsControl.h"
using namespace Environment;

#include "ControlWindow.h"
#include "LimitedExponentialInterpolation.h"
using namespace std::chrono_literals;

GraphicsControl::GraphicsControl(MBoundaries * InBoundaries, pxMargins InMargins)
	: MBoundaries(InBoundaries, InMargins),
	Space(
		this,
		pxMargins(0,0,0,0),
		fColor(1, 1, 1),
		[this]() {return GeometryObject::MakeRectangle(pxPoint(0, 0), GetSize().ToPoint()); },
		nullptr,
		EScrollMode::Background),
	SelectionBorder(
		this,
		pxMargins(0, 0, 0, 0),
		Interpolator<fColor>(fColor(1, 1, 1, 0), new LimitedExponentialInterpolation<fColor>(300ms)),
		[this]() {return GeometryObject::MakeRectangle(pxPoint(2, 2), GetSize().ToPoint() - pxPoint(2,2)); },
		nullptr,
		EScrollMode::Background)
{
	GetWindow()->CommonFilledGeometryLayer.AddObject(&Space);
	GetWindow()->CommonUnfilledGeometryLayer.AddObject(&SelectionBorder);
}

void GraphicsControl::Event_CharacterEntered(unsigned int InChar)
{
}

void GraphicsControl::Event_KeyChanged(EventInfo_KeyChanged const & InInfo)
{
}

void GraphicsControl::Event_SelectionChanged(EventInfo_SelectionChanged const & InInfo)
{
	if (InInfo == ESelectionStatus::Selected)
	{
		SelectionBorder.Color = fColor(0.2, 0, 1);
		bSelected = true;
	}
	else
	{
		SelectionBorder.Color = fColor(0, 0, 0, 0);
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
