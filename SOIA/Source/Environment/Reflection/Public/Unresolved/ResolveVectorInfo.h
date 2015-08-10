
#pragma once

#include "ResolveInfoInterface.h"
#include "VoidPointerToUnresolvedRObject.h"
#include "ElementID.h"

namespace Environment
{
	class RContainer;
	class LIBIMPEXP ResolveVectorInfo : public ResolveInfoInterface
	{
	public:
		ResolveVectorInfo(const std::vector<VoidPointerToUnresolvedRObject>& InObjects, RContainer* InContainer);

		virtual void OverrideContainer(RContainer*) override;

		std::vector<VoidPointerToUnresolvedRObject> Objects;
		RContainer* TargetElementContainer;
	};
}