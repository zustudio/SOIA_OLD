
#include "Definitions.h"

#include "InPort.h"
using namespace Supervisor;
using namespace Environment;

InPort::InPort()
	: Port(PortConfiguration::Input)
{

}

bool InPort::Write(const VoidPointer& InData)
{
	InputBuffer.push_back(InData);
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