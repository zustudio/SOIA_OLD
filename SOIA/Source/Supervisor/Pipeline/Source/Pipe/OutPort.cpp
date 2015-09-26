
#include "Definitions.h"

#include "OutPort.h"
using namespace Supervisor;
using namespace Environment;

OutPort::OutPort(Environment::Thread* InOwner, TypeID InType)
	: Port(InOwner, PortConfiguration::Output, InType),
	CurrentOutput(VoidPointer::Nullpointer())
{
}

bool OutPort::Write(const Environment::VoidPointer& InData)
{
	CurrentOutput = InData;
	Partner->Write(CurrentOutput);
	Partner->WakeUp();
	return true;
}

bool OutPort::Read(Environment::VoidPointer& OutData)
{
	OutData = CurrentOutput;
	return true;
}