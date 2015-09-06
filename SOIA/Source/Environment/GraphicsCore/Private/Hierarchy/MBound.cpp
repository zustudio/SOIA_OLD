
#include "Definitions.h"

#include "MBound.h"
using namespace Environment;

#include "MBoundaries.h"

void MBound::SetBoundaries(MBoundaries * InBoundaries)
{
	Boundaries = InBoundaries;
	InBoundaries->AddBoundObject(this);
}
