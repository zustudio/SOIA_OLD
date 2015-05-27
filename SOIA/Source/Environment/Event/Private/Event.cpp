
#include "Environment/PreProcessor/Classes/PrivateDefinitions.h"

#include "Environment/Event/Public/Event.h"
using namespace Environment;

#include "Environment/Reflection/Element/Public/RFunctionInterface.h"
#include <assert.h>

void Event::Raise(EventDetails* InDetails)
{
	for (auto function : HandlerFunctions)
	{
		function->Execute({InDetails});
	}
}

void Event::AddHandlerFunction(RFunctionInterface* InFunction)
{
	assert(InFunction);

	HandlerFunctions.push_back(InFunction);
}
