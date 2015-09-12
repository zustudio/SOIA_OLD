
#pragma once

#include "fPoint.h"
#include "pxPoint.h"
#include "pxSize.h"
#include "pxMargins.h"

#include <functional>


namespace Environment
{
	class MBoundaries;
}

namespace Environment
{
	class LIBIMPEXP MBound
	{

	public:
		//----- ctor -----
		MBound(MBoundaries* InBoundaries, pxMargins InMargins);
		MBound(MBound const &) = delete;
		MBound(MBound &&);
		MBound& operator=(MBound const &) = delete;
		MBound& operator=(MBound&& InOther);
		virtual ~MBound();

		void SetDestructorCallback(std::function<void(MBound*)> const & InDestructorFunction);

		virtual void RequestUpdate();
		virtual void Update();

		virtual MBoundaries* GetTopBoundaries();

		pxSize GetSize();
		fPoint CalculateRelativeLocationOnWindow(pxPoint InPoint);

		virtual Vector2D<pxPoint> CalculateAbsoluteCornerLocationsOnWindow();

	protected:
		bool AssertBoundariesValid();

	public:
		bool bUpdateRequested;

	protected:
		MBoundaries* Boundaries;
		pxMargins Margins;

		bool bMovedAway;
		std::function<void(MBound*)> DestructorFunction;
	};
}
