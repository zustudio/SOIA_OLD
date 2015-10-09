
#include "Definitions.h"

#include "MBoundaries.h"
using namespace Environment;

#include "RenderTarget.h"
#include "GraphicsWindow.h"
#include "LimitedExponentialInterpolation.h"
#include "SmoothInterpolation.h"
#include "LinearInterpolation.h"

#include <algorithm>

using namespace std::chrono_literals;

MBoundaries::MBoundaries(MBoundaries * InBoundaries, pxMargins InMargins)
	: MBound(InBoundaries, InMargins),
	ScrollOffset(pxPoint(0,0), new SmoothInterpolation<pxPoint>(150ms))
{}

void MBoundaries::RequestUpdate()
{
	MBound::RequestUpdate();
	for (MBound* object : BoundObjects)
	{
		object->RequestUpdate();
	}
}

void MBoundaries::Update()
{
	MBound::Update();

	// interpolate offset
	ScrollOffset.Update();
	if (ScrollOffset.IsInterpolating())
		this->RequestUpdate();

	// update children
	for (MBound* object : BoundObjects)
	{
		object->Update();
	}

	// calculate virtual size
	pxPoint furthestPoint = GetSize().ToPoint();
	for (MBound* object : BoundObjects)
	{
		if (object->GetScrollMode() == EScrollMode::Content)
		{
			auto o = object->CalculateAbsoluteCornerLocationsOnWindow().Y;
			auto me = CalculateAbsoluteCornerLocationsOnWindow().X;
			pxPoint bottomRight = o - me;
			furthestPoint.X = furthestPoint.X > bottomRight.X ? furthestPoint.X : bottomRight.X;
			if (furthestPoint.Y < bottomRight.Y)
				furthestPoint.Y = bottomRight.Y;
		}
	}
	pxSize newVirtualSize = pxSize(furthestPoint.X, furthestPoint.Y);
	if (newVirtualSize != VirtualSize)
	{
		VirtualSize = newVirtualSize;
		Event_VirtualSizeChanged(newVirtualSize);
	}
}

Interpolator<pxPoint> const & MBoundaries::GetScrollOffset()
{
	return ScrollOffset;
}

pxSize MBoundaries::GetVirtualSize()
{
	return VirtualSize;
}

void MBoundaries::Scroll(pxPoint InOffset)
{
	pxSize size = GetSize();
	pxPoint offset = ScrollOffset.GetTarget();

	offset += InOffset;
	offset.X = offset.X > 0 ? offset.X : 0;
	offset.Y = offset.Y > 0 ? offset.Y : 0;
	
	if (offset.X + size.Width > VirtualSize.Width)
		offset.X = VirtualSize.Width - size.Width;

	if (offset.Y + size.Height > VirtualSize.Height)
		offset.Y = VirtualSize.Height - size.Height;

	ScrollOffset = offset;

	RequestUpdate();
}

MBoundaries * MBoundaries::GetTopBoundaries()
{
	if (Boundaries)
		return Boundaries->GetTopBoundaries();
	else
		return this;
}

void MBoundaries::Event_VirtualSizeChanged(pxSize const & InNewSize)
{
	///\todo Make window scroll automatically, if virtualsize gets smaller
}

RenderTarget* MBoundaries::GetRenderTarget()
{
	RenderTarget* target = dynamic_cast<RenderTarget*>(this);
	return target ? target : Boundaries->GetRenderTarget();
}

std::vector<MBound*> const & MBoundaries::GetBoundObjects()
{
	return BoundObjects;
}

void MBoundaries::AddBoundObject(MBound * InBoundObject)
{
	BoundObjects.push_back(InBoundObject);
}

void MBoundaries::RemoveBoundObject(MBound* InBoundObject)
{
	auto iter_boundObject = std::find(BoundObjects.begin(), BoundObjects.end(), InBoundObject);

	if (iter_boundObject != BoundObjects.end())
		BoundObjects.erase(iter_boundObject);
}

GraphicsWindow* MBoundaries::GetWindow()
{
	return dynamic_cast<GraphicsWindow*>(GetTopBoundaries());
}
