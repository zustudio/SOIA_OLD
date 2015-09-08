
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

pxPoint pxSize::ToPoint()
{
	return pxPoint(Width, Height);
}
