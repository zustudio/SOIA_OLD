
#include "Definitions.h"

#include "Pipe.h"
using namespace Supervisor;
using namespace Environment;

#include "LogProvider.h"

Pipe::Pipe(Environment::RFunction* InFunction)
	: BaseType(),
	TargetFunction(InFunction)
{
	bool result = true;
	auto argumentTypes = InFunction->GetArgumentTypes();
	for (auto argumentType : argumentTypes)
	{
		if (argumentType.IsReference())
		{
			if (argumentType.IsConst())
			{
				Input.push_back(InPort(this, argumentType));
			}
			else
			{
				Output.push_back(OutPort(this, argumentType));
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
}

void Pipe::Main()
{
	while (!IsStopping())
	{
		std::vector<VoidPointer> args;
		for (int i = 0; i < Input.size(); i++)
		{
			VoidPointer inData = VoidPointer::Nullpointer();

			while (!Input[i].Read(inData))
				Sleep();

			args.push_back(inData);
		}

		TargetFunction->CorrectArgsAndExecute(args);

		int offset = Input.size();
		int max = Output.size();
		for (int i = 0; i < max; i++)
		{
			Output[i].Write(args[i + offset]);
		}
	}
}

