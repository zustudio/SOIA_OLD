
#include "Environment/PreProcessor/Classes/PrivateDefinitions.h"

#include "Environment/Reflection/Element/Public/RService.h"
using namespace Environment;

RService::RService(RContainer &InContainer) : RContainer(Range<int>(0,100))
{
	Services = &InContainer;
}