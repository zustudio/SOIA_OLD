#pragma once

#include "pxPoint.h"
#include "Vector2D.h"

namespace SO
{
	namespace Drawing
	{
		class fPoint : public ZABS::Math::Vector2D<float>
		{
		public:
			//init
			fPoint();
			fPoint(float newX, float newY);
			fPoint(const fPoint &equalPoint);
			fPoint(const ZABS::Math::Vector2D<float> &equalPoint);
			//conversion
			virtual pxPoint ToPxPoint(const pxPoint &absolutSpaceSize);
		};
	}
}
