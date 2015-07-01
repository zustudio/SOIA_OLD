
#include "Definitions.h"

#include "Pipe.h"
using namespace Supervisor;
using namespace Environment;

#include "LogProvider.h"

Pipe::Pipe()
	: BaseType()
{

}

bool Pipe::SetAnalyzerFunction(RFunction* InFunction)
{
	bool result = true;
	auto argumentTypes = InFunction->GetArgumentTypes();
	for (auto argumentType : argumentTypes)
	{
		if (argumentType.IsReference())
		{
			if (argumentType.IsConst())
			{
				Input.push_back(InPort(argumentType));
			}
			else
			{
				Output.push_back(OutPort(argumentType));
			}
		}
		else
		{
			result = false;
			LOG("Argument type of passed function interface for creating pipe was not a reference (" 
				+ argumentType.ToString() + "). Canceled.", Logger::Severity::Warning);
			break;
		}
	}
	if (!Input.size())
	{
		LOG("There must be at least an input.", Logger::Severity::Warning);
		result = false;
	}
	else if (!Output.size())
	{
		LOG("There must be at least an output.", Logger::Severity::Warning);
		result = false;
	}
	return result;
}