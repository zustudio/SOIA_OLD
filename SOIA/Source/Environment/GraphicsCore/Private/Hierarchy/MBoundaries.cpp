
#include "Definitions.h"

#include "MBoundaries.h"
using namespace Environment;

#include "MBound.h"

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

MBoundaries * MBoundaries::GetTopBoundaries()
{
	if (Boundaries)
		return Boundaries->GetTopBoundaries();
	else
		return this;
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
