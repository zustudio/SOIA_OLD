
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
	for (MBound* object : BoundObjects)
	{
		object->Update();
	}
}

pxPoint MBoundaries::GetScrollOffset()
{
	return ScrollOffset;
}

void MBoundaries::Scroll(pxPoint InOffset)
{
	ScrollOffset += InOffset;
	RequestUpdate();
}

MBoundaries * MBoundaries::GetTopBoundaries()
{
	if (Boundaries)
		return Boundaries->GetTopBoundaries();
	else
		return this;
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
