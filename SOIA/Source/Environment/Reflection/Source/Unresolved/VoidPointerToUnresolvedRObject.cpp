
#include "Definitions.h"

#include "VoidPointerToUnresolvedRObject.h"
using namespace Environment;

#include "RContainer.h"

void VoidPointerToUnresolvedRObject::Resolve(RContainer* InContainer)
{
	ResolveInfo->OverrideContainer(InContainer);
	ResolveFunction(this);
}

ResolveInfoInterface* VoidPointerToUnresolvedRObject::GetResolveInfo()
{
	return ResolveInfo;
}