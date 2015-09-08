
#pragma once

#include "MBound.h"

namespace Environment
{
	class GraphicsObject : public MBound
	{
	public:
		GraphicsObject(MBoundaries* InBoundaries, pxMargins InMargins);

		bool bChanged;
	};
}