
#include "Definitions.h"

#include "Port.h"
using namespace Supervisor;
using namespace Environment;

Port::Port(PortConfiguration InConfiguration, TypeID InType)
	:
	Configuration(InConfiguration),
	Type(InType)
{}

bool Port::Pair(Port* InPartner)
{
	if (InPartner->Configuration != Configuration)
	{
		InPartner->Partner = this;
		Partner = InPartner;
		return true;
	}
	else
	{
		return false;
	}
}

TypeID Port::GetType()
{
	return Type;
}