
#include "Definitions.h"

#include "MBoundaries.h"
using namespace Environment;

#include "MBound.h"

void MBoundaries::AddBoundObject(MBound * InBoundObject)
{
	BoundObjects.push_back(InBoundObject);
}
