
#include "Definitions.h"

#include "RService.h"
using namespace Environment;

RService::RService(RContainer &InContainer) : RContainer(Range<int>(0,100))
{
	Services = &InContainer;
}