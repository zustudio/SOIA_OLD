
#pragma once

#include "MBound.h"

#include "Range.h"

namespace Environment
{
	class GraphicsObject : public MBound
	{
	public:
		GraphicsObject(MBoundaries* InBoundaries, pxMargins InMargins);

		Range<int> VertexBufferRange;
		Range<int> ElementBufferRange;
	};
}