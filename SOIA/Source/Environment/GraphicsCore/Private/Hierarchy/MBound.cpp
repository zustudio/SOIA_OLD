
#include "Definitions.h"

#include "MBound.h"
using namespace Environment;

#include "MBoundaries.h"
#include "GlobalLogger.h"

#include <assert.h>

MBound::MBound(MBoundaries * InBoundaries, pxMargins InMargins)
	:
	Boundaries(InBoundaries),
	Margins(InMargins),
	bMovedAway(false)
{
	if (InBoundaries)
		InBoundaries->AddBoundObject(this);
}

MBound::MBound(MBound && InOther)
	:
	Boundaries(InOther.Boundaries),
	Margins(InOther.Margins),
	bMovedAway(false),
	DestructorFunction(nullptr)
{
	if (Boundaries)
		Boundaries->AddBoundObject(this);
}


MBound& MBound::operator=(MBound && InOther)
{
	Boundaries = InOther.Boundaries;
	Margins = InOther.Margins;

	//InOther.bMovedAway = true;

	return *this;
}

MBound::~MBound()
{
	LOG("Destroying MBound '" + std::to_string((int)this) + "'", Logger::Severity::DebugInfo);

	if (Boundaries)
		Boundaries->RemoveBoundObject(this);
	if (DestructorFunction)
		DestructorFunction(this);
}

void MBound::SetDestructorCallback(std::function<void(MBound*)> const & InDestructorFunction)
{
	DestructorFunction = InDestructorFunction;
}

void MBound::RequestUpdate()
{
	bUpdateRequested = true;
}

void MBound::Update()
{
}

pxSize MBound::GetSize()
{
	auto corners = CalculateAbsoluteCornerLocationsOnWindow();
	pxPoint size = corners.Y - corners.X;
	return pxSize(size.X, size.Y);
}

MBoundaries* MBound::GetTopBoundaries()
{
	if (Boundaries)
		return Boundaries->GetTopBoundaries();
	else
		return nullptr;
}

fPoint MBound::CalculateRelativeLocationOnWindow(pxPoint InPoint)
{
	pxPoint absolutePoint = CalculateAbsoluteCornerLocationsOnWindow().X + InPoint;
	pxSize absoluteSize = GetTopBoundaries()->GetSize();

	fPoint result = fPoint(float(absolutePoint.X) / float(absoluteSize.Width), float(absoluteSize.Height - absolutePoint.Y) / float(absoluteSize.Height));

	return result * 2 - fPoint(1,1);
}

Vector2D<pxPoint> MBound::CalculateAbsoluteCornerLocationsOnWindow()
{
	// check that i have parent boundaries
	if (!AssertBoundariesValid())
	{
		return Vector2D<pxPoint>(pxPoint(0, 0), pxPoint(100, 100));
	}
	// check that there are at most 2 negative margins (meaning absolute size)
	else if (true != (Margins.Left >= 0 || Margins.Right >= 0) && (Margins.Top >= 0 || Margins.Bottom >= 0))
	{
		LOG("Object's Margins do not allow a proper corner calculation.", Logger::Severity::Warning);
		return Vector2D<pxPoint>(pxPoint(0, 0), pxPoint(100, 100));
	}

	int realLeftMargin = Margins.Left >= 0 ? Margins.Left : Boundaries->GetSize().Width + Margins.Left - Margins.Right;
	int realRightMargin = Margins.Right >= 0 ? Margins.Right : Boundaries->GetSize().Width + Margins.Right - Margins.Left;

	int realTopMargin = Margins.Top >= 0 ? Margins.Top : Boundaries->GetSize().Height + Margins.Top - Margins.Bottom;
	int realBottomMargin = Margins.Bottom >= 0 ? Margins.Bottom : Boundaries->GetSize().Height + Margins.Bottom - Margins.Top;

	Vector2D<pxPoint> calculatedMarginCorrection = Vector2D<pxPoint>(pxPoint(realLeftMargin, realTopMargin), pxPoint(-realRightMargin, -realBottomMargin));
	return Boundaries->CalculateAbsoluteCornerLocationsOnWindow() + calculatedMarginCorrection;
}

bool MBound::AssertBoundariesValid()
{
	bool result = true;
	if (!Boundaries)
	{
		LOG("Object has no boundaries.", Logger::Severity::Warning);
		result = false;
	}
	return result;
}
