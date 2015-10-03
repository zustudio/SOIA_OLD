
#include "Definitions.h"

#include "MBoundaries.h"
using namespace Environment;

#include "RenderTarget.h"
#include "GraphicsWindow.h"

#include <algorithm>

MBoundaries::MBoundaries(MBoundaries * InBoundaries, pxMargins InMargins)
	: MBound(InBoundaries, InMargins)
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
	// update children
	for (MBound* object : BoundObjects)
	{
		object->Update();
	}

	// calculate virtual size
	pxPoint furthestPoint = pxPoint(0, 0);
	for (MBound* object : BoundObjects)
	{
		pxPoint bottomRight = object->CalculateAbsoluteCornerLocationsOnWindow().Y;
		furthestPoint.X = furthestPoint.X > bottomRight.X ? furthestPoint.X : bottomRight.X;
		furthestPoint.Y = furthestPoint.Y > bottomRight.Y ? furthestPoint.Y : bottomRight.Y;
	}
	furthestPoint += ScrollOffset;
	pxSize newVirtualSize = pxSize(furthestPoint.X, furthestPoint.Y);
	if (newVirtualSize != VirtualSize)
	{
		VirtualSize = newVirtualSize;
		Event_VirtualSizeChanged(newVirtualSize);
	}
}

pxPoint MBoundaries::GetScrollOffset()
{
	return ScrollOffset;
}

pxSize Environment::MBoundaries::GetVirtualSize()
{
	return VirtualSize;
}

void MBoundaries::Scroll(pxPoint InOffset)
{
	pxSize size = GetSize();
	ScrollOffset += InOffset;
	ScrollOffset.X = ScrollOffset.X > 0 ? ScrollOffset.X : 0;
	ScrollOffset.Y = ScrollOffset.Y > 0 ? ScrollOffset.Y : 0;
	
	if (ScrollOffset.X + size.Width > VirtualSize.Width)
		ScrollOffset.X = VirtualSize.Width - size.Width;

	if (ScrollOffset.Y + size.Height > VirtualSize.Height)
		ScrollOffset.Y = VirtualSize.Height - size.Height;

	RequestUpdate();
}

MBoundaries * MBoundaries::GetTopBoundaries()
{
	if (Boundaries)
		return Boundaries->GetTopBoundaries();
	else
		return this;
}

void MBoundaries::Event_VirtualSizeChanged(pxSize InNewSize)
{
	///\todo Make window scroll automatically, if virtualsize gets smaller
}

RenderTarget* MBoundaries::GetRenderTarget()
{
	RenderTarget* target = dynamic_cast<RenderTarget*>(this);
	return target ? target : Boundaries->GetRenderTarget();
}

std::vector<MBound*>& MBoundaries::GetBoundObjects()
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
