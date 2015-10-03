
#include "Definitions.h"

#include "ScrollBar.h"
using namespace Env;

ScrollBar::ScrollBar(MBoundaries * InBoundaries, EScrollBarConfiguration InConfiguration)
	: GeometryObject(
		InBoundaries,
		InConfiguration == EScrollBarConfiguration::Vertical ?
			pxMargins(-3, 1, 1, 1) :
			pxMargins(1, -3, 1, 1),
		fColor(1, 0, 0, 1),
		VectorND<pxPoint>({}),
		EScrollMode::Background)
{}

void ScrollBar::Set(float InSize, float InOffset)
{
	int height = GetSize().Height;
	int offset = height * InOffset;
	int size = height * InSize;

	pxPoint topLeft = pxPoint(0, offset);
	pxPoint bottomRight = pxPoint(3, offset + size);

	Edges = GeometryObject::MakeRectangle(topLeft, bottomRight);
}
