#pragma once

#include "Vector2D.h"

namespace Environment
{
	class LIBIMPEXP pxPoint : public Vector2D<int>
	{
	public:
		//---- init ----
		pxPoint(int newX = 0, int newY = 0);
		pxPoint(const Vector2D<int> &equalVector2D);

	};
}
