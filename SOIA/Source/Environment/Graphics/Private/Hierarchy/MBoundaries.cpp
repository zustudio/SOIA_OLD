
#include "Definitions.h"

#include "MBoundaries.h"
using namespace Environment;

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
