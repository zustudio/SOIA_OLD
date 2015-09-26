
#include "Definitions.h"

#include "ResolveVectorInfo.h"
using namespace Environment;

#include "RContainer.h"

ResolveVectorInfo::ResolveVectorInfo(const std::vector<VoidPointerToUnresolvedRObject>& InObjects, RContainer* InContainer)
	:
	Objects(InObjects),
	TargetElementContainer(InContainer)
{}

void ResolveVectorInfo::OverrideContainer(RContainer* InContainer)
{
	TargetElementContainer = InContainer;
}