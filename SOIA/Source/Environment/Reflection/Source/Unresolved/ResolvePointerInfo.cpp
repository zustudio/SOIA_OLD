
#include "Definitions.h"

#include "ResolvePointerInfo.h"
using namespace Environment;

#include "RContainer.h"

ResolvePointerInfo::ResolvePointerInfo(ElementID InID, RContainer* InContainer)
	:
	TargetElementID(InID),
	TargetElementContainer(InContainer)
{}

void ResolvePointerInfo::OverrideContainer(RContainer* InContainer)
{
	TargetElementContainer = InContainer;
}