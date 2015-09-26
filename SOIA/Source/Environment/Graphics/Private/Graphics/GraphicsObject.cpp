
#include "Definitions.h"

#include "GraphicsObject.h"
using namespace Environment;

GraphicsObject::GraphicsObject(MBoundaries * InBoundaries, pxMargins InMargins, EScrollMode InScrollMode)
	: MBound(InBoundaries, InMargins, InScrollMode),
	VertexBufferRange(Range<int>::Empty()),
	ElementBufferRange(Range<int>::Empty())
{}
