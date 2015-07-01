
#pragma once

// include super class
#include "Environment/Reflection/Element/Public/RElement.h"

// include SOIA
#include "EventDetails.h"

namespace Environment
{
class RFunctionInterface;
class DLLIMPEXP Event : public RElement
{
public:
	void Raise(EventDetails* InDetails = nullptr);

	void AddHandlerFunction(RFunctionInterface* InFunction);

private:
	std::vector<RFunctionInterface*> HandlerFunctions;
};
}
