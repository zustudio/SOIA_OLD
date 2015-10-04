
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
	enum class EScrollMode : int
	{
		Content,
		Background
	};

	class LIBIMPEXP MBound
	{

	public:
		//----- ctor -----
		MBound(MBoundaries* InBoundaries, pxMargins InMargins, EScrollMode InScrollMode = EScrollMode::Content);
		MBound(MBound const &) = delete;
		MBound(MBound &&);
		MBound& operator=(MBound const &) = delete;
		MBound& operator=(MBound&& InOther);
		virtual ~MBound();

		void SetDestructorCallback(std::function<void(MBound*)> const & InDestructorFunction);

		virtual void RequestUpdate();
		virtual void Update();

		virtual MBoundaries* GetTopBoundaries();
		pxMargins const & GetMargins();

		pxSize GetSize();
		fPoint CalculateRelativeLocationOnWindow(pxPoint InPoint);

		virtual Vector2D<pxPoint> CalculateAbsoluteCornerLocationsOnWindow();

		EScrollMode GetScrollMode();

	protected:
		bool AssertBoundariesValid();

	public:
		bool bUpdateRequested;

	protected:
		MBoundaries* Boundaries;
		pxMargins Margins;
		EScrollMode ScrollMode;

		std::function<void(MBound*)> DestructorFunction;
	};
}
