
#pragma once

#include "ResolveInfoInterface.h"
#include "ElementID.h"

namespace Environment
{
	class RContainer;
	class LIBIMPEXP ResolvePointerInfo : public ResolveInfoInterface
	{
	public:
		ResolvePointerInfo(ElementID InID, RContainer* InContainer);

		virtual void OverrideContainer(RContainer*) override;

		ElementID TargetElementID;
		RContainer* TargetElementContainer;
	};
}