
#pragma once

#include "MBound.h"

#include "Range.h"

namespace Environment
{
	class GraphicsObject : public MBound
	{
	public:
		GraphicsObject(MBoundaries* InBoundaries, pxMargins InMargins);

		virtual void Update();

		Range<int> VertexBufferRange;
		Range<int> ElementBufferRange;
		bool bDirty;
	};
}