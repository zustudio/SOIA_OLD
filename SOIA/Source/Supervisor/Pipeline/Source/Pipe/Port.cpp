
#include "Definitions.h"

#include "Port.h"
using namespace Supervisor;
using namespace Environment;

Port::Port(Environment::Thread* InOwner, PortConfiguration InConfiguration, TypeID InType)
	:
	Owner(InOwner),
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

void Port::WakeUp()
{
	Owner->WakeUp();
}

TypeID Port::GetType()
{
	return Type;
}