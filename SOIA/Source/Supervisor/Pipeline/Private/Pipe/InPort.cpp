
#include "Definitions.h"

#include "InPort.h"
using namespace Supervisor;
using namespace Environment;

InPort::InPort(Environment::Thread* InOwner, TypeID InType)
	: Port(InOwner, PortConfiguration::Input, InType)
{}

bool InPort::Write(const VoidPointer& InData)
{
	InputBuffer.push_back(InData);
	return true;
}

bool InPort::Read(VoidPointer &OutData)
{
	if (InputBuffer.size())
	{
		OutData = InputBuffer[0];
		InputBuffer.pop_front();
		return true;
	}
	else
	{
		return false;
	}
}