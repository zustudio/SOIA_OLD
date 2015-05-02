
#pragma once

// include super class
#include "Environment/Reflection/Element/Public/RElement.h"

// include SOIA
#include "EventDetails.h"
#include "Environment/Reflection/Element/Public/RFunctionInterface.h"

namespace Environment
{
class DLLIMPEXP Event : RElement
{
public:
	void Raise(EventDetails* InDetails = nullptr);

	void AddHandlerFunction(RFunctionInterface* InFunction);

private:
	std::vector<RFunctionInterface*> HandlerFunctions;
};
}
