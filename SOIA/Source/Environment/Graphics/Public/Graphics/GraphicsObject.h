
#pragma once

#include "MBound.h"

#include "Range.h"

namespace Environment
{
	class GraphicsObject : public MBound
	{
	public:
		GraphicsObject(MBoundaries* InBoundaries, pxMargins InMargins, EScrollMode InScrollMode = EScrollMode::Content);

		Range<int> VertexBufferRange;
		Range<int> ElementBufferRange;
	};
}