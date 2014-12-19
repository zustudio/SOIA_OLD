#pragma once

#include "Vector2D.h"

using namespace ZABS::Math;

namespace SO
{
	namespace Drawing
	{
		class pxPoint : public Vector2D<int>
		{
		public:
			//init
			pxPoint();
			pxPoint(const pxPoint &equalPoint);
			pxPoint(int newX, int newY);
		};
	}
}
