#pragma once

#include "pxPoint.h"
#include "Vector2D.h"

namespace Graphics
{
	class LIBIMPEXP fPoint : public ZABS::Math::Vector2D<float>
	{
	public:
		//---- init ----
		fPoint(float newX = 0, float newY = 0);
		fPoint(const ZABS::Math::Vector2D<float> &equalPoint);
		virtual ~fPoint();
		//---- conversion ----
		virtual pxPoint ToPxPoint(pxPoint &absolutSpaceSize);
	};
}
