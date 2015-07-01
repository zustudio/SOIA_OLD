
#pragma once

#include "ResolveInfoInterface.h"
#include "Element_ID.h"

namespace Environment
{
	class RContainer;
	class LIBIMPEXP ResolvePointerInfo : public ResolveInfoInterface
	{
	public:
		ResolvePointerInfo(Element_ID InID, RContainer* InContainer);

		virtual void OverrideContainer(RContainer*) override;

		Element_ID TargetElementID;
		RContainer* TargetElementContainer;
	};
}