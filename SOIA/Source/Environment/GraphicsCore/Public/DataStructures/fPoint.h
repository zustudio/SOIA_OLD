#pragma once

#include "Vector2D.h"

#include "DataUnravelerTemplate.h"

namespace Environment
{
	class LIBIMPEXP fPoint : public Vector2D<float>
	{
	public:
		// data unraveler definition
		using DataUnraveler = DataUnravelerTemplate<Vector2D, float, &fPoint::X, &fPoint::Y>;

		//---- init ----
		fPoint(float newX = 0, float newY = 0);
		fPoint(const Vector2D<float> &equalPoint);
		virtual ~fPoint();
		
	};
}
