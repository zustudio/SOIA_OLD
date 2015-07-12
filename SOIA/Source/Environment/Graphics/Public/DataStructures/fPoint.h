#pragma once

#include "pxPoint.h"
#include "Vector2D.h"

namespace Environment
{
	class LIBIMPEXP fPoint : public Vector2D<float>
	{
	public:
		//---- init ----
		fPoint(float newX = 0, float newY = 0);
		fPoint(const Vector2D<float> &equalPoint);
		virtual ~fPoint();
		//---- conversion ----
		virtual pxPoint ToPxPoint(pxPoint &absolutSpaceSize);
	};
}
