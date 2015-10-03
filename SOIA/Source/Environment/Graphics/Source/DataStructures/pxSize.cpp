
#include "Definitions.h"

#include "pxSize.h"
using namespace Environment;

pxSize::pxSize()
	:
	Width(0),
	Height(0)
{}

pxSize::pxSize(int InWidth, int InHeight)
	:
	Width(InWidth),
	Height(InHeight)
{}

bool pxSize::operator==(pxSize const & InOther) const
{
	return Width == InOther.Width && Height == InOther.Height;
}

bool Environment::pxSize::operator!=(pxSize const & InOther) const
{
	return Width != InOther.Width || Height != InOther.Height;
}

pxPoint pxSize::ToPoint()
{
	return pxPoint(Width, Height);
}
