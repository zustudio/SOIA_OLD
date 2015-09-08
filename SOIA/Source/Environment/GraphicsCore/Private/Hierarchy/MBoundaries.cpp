
#include "Definitions.h"

#include "MBoundaries.h"
using namespace Environment;

#include "MBound.h"

MBoundaries::MBoundaries(MBoundaries * InBoundaries, pxMargins InMargins)
	: MBound(InBoundaries, InMargins)
{}

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