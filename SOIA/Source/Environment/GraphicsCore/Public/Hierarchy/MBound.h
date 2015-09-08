
#pragma once

#include "fPoint.h"
#include "pxPoint.h"
#include "pxSize.h"
#include "pxMargins.h"


namespace Environment
{
	class MBoundaries;
}

namespace Environment
{
	class MBound
	{

	public:
		MBound(MBoundaries* InBoundaries, pxMargins InMargins);

		virtual MBoundaries* GetTopBoundaries();

		pxSize GetSize();
		fPoint CalculateRelativeLocationOnWindow(pxPoint InPoint);

		virtual Vector2D<pxPoint> CalculateAbsoluteCornerLocationsOnWindow();

	protected:
		bool AssertBoundariesValid();
		MBoundaries* Boundaries;
		pxMargins Margins;
	};
}
