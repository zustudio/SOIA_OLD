
#include "Definitions.h"

#include "GraphicsObject.h"
using namespace Environment;

GraphicsObject::GraphicsObject(MBoundaries * InBoundaries, pxMargins InMargins)
	: MBound(InBoundaries, InMargins),
	VertexBufferRange(Range<int>::Empty()),
	ElementBufferRange(Range<int>::Empty()),
	bDirty(true)
{}

void GraphicsObject::MarkDirty()
{
	bDirty = true;
}
