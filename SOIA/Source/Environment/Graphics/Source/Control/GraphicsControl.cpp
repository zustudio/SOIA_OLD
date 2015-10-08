
#include "Definitions.h"

#include "GraphicsControl.h"
using namespace Environment;

#include "ControlWindow.h"
#include "LimitedExponentialInterpolation.h"
using namespace std::chrono_literals;

GraphicsControl::GraphicsControl(MBoundaries * InBoundaries, pxMargins InMargins, StyleSheet const & InStyle)
	: RenderTarget(InBoundaries, InMargins, InStyle),
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
		Interpolator<fColor>(fColor(0, 0, 0, 0), new LimitedExponentialInterpolation<fColor>(150ms)),
		[this]() {return GeometryObject::MakeRectangle(pxPoint(1, 0), GetSize().ToPoint() - pxPoint(0, 1)); },
		nullptr,
		EScrollMode::Background),
	VerticalScrollBar(
		this,
		EScrollBarConfiguration::Vertical)
{
	AddObject(&Space, Layer_Background);
	AddObject(&SelectionBorder, Layer_UnfilledGeometry);
	AddObject(&VerticalScrollBar, Layer_FilledGeometry);
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
		SelectionBorder.Color = fColor(1, 0.5, 0);
		bSelected = true;
	}
	else
	{
		SelectionBorder.Color = fColor(0.2, 0, 0);
		bSelected = false;
	}
}

void GraphicsControl::Event_VirtualSizeChanged(pxSize const & InNewSize)
{
	float size = GetSize().Height / float(InNewSize.Height);
	VerticalScrollBar.SetSize(size);
}

void GraphicsControl::Event_Scroll(Vector2D<double> const & InDelta)
{
	pxPoint delta;
	delta.X = InDelta.X * 40;
	delta.Y = InDelta.Y * -40;
	Scroll(delta);

	float offset = float(GetScrollOffset().GetTarget().Y) / GetVirtualSize().Height;
	VerticalScrollBar.SetOffset(offset);
}

bool GraphicsControl::IsSelected()
{
	return bSelected;
}

