
#include "Definitions.h"

#include "TCalculator.h"
using namespace Supervisor;
using namespace Environment;

#include "GlobalLogger.h"


TCalculator::TCalculator()
	: BaseType(),
	CurrentMathContainer(new MathContainer())
{
	ReflectAttributes();
}

bool TCalculator::cmd_calc(const std::string& InEq)
{
	bool success = false;
	DynamicMathFunction* function = CurrentMathContainer->ParseString(InEq);
	if (function)
	{
		
		if (function->GetName() == "")
		{
			Dialogue->WriteLine("=" + std::to_string(function->Execute({})));
		}
		else
		{
			Functions.push_back(function);
			Dialogue->WriteLine("Done.");
		}
		success = true;
	}
	return success;
}

bool TCalculator::pipe_calculate2d(std::string const & InFuncName, double const & InX, double & OutY)
{
	bool success = false;
	for (DynamicMathFunction* function : Functions)
	{
		if (function->GetName() == InFuncName)
		{
			OutY = function->Execute({ InX });
			success = true;
		}
	}

	if (!success)
	{
		LOG("Could not find function '" + InFuncName + "'.", Logger::Severity::Error);
	}

	return success;
}
