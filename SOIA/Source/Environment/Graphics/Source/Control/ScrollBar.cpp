
#include "Definitions.h"

#include "ScrollBar.h"
using namespace Env;

#include "LimitedExponentialInterpolation.h"
using namespace std::chrono_literals;

ScrollBar::ScrollBar(MBoundaries * InBoundaries, EScrollBarConfiguration InConfiguration)
	: GeometryObject(
		InBoundaries,
		InConfiguration == EScrollBarConfiguration::Vertical ?
			pxMargins(-3, 1, 1, 1) :
			pxMargins(1, -3, 1, 1),
		fColor(0.5, 0.5, 0.5, 0.5),
		Interpolator<VectorND<pxPoint>>(VectorND<pxPoint>({}), new LimitedExponentialInterpolation<VectorND<pxPoint>>(200ms)),
		EScrollMode::Background),
	Size(0),
	Offset(0)
{}

void ScrollBar::SetSize(float InSize)
{
	Size = InSize;
	UpdateEdges();
}

void ScrollBar::SetOffset(float InOffset)
{
	Offset = InOffset;
	UpdateEdges();
}

void ScrollBar::UpdateEdges()
{
	int height = GetSize().Height;
	int offset = height * Offset;
	int size = height * Size;

	pxPoint topLeft = pxPoint(0, offset);
	pxPoint bottomRight = pxPoint(3, offset + size);

	Edges = GeometryObject::MakeRectangle(topLeft, bottomRight);
	this->RequestUpdate();
}
