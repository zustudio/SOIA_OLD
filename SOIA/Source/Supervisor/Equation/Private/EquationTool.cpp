
#include "Definitions.h"

#include "EquationTool.h"
using namespace Supervisor;
using namespace Environment;

#include "EquationString.h"

REquationTool::REquationTool(const RPointer<RDialogue>& InDialogue)
	: BaseType(InDialogue),
	CurrentMathContainer(nullptr)
{
	ReflectAttributes();
}

bool REquationTool::cmd_calc(const std::string& InEqName, const double& Argument)
{
	bool success = false;
	if (CurrentMathContainer)
	{
		for (auto Eq : Equations)
		{
			if (Eq.GetFunctionID().Name == InEqName)
			{
				double result = Eq.Calculate(Argument);
				Dialogue->WriteLine(" =" + std::to_string(result));
				success = true;
			}
		}
	}
	return success;
}

bool REquationTool::cmd_storeeq(const std::string& InString)
{
	bool result = false;
	if (CurrentMathContainer)
	{
		Equations.push_back(EquationString(InString).Parse(*CurrentMathContainer));
		result = true;
	}
	return result;
}

bool REquationTool::cmd_setmathcontainer(MathContainer* const & InMathContainer)
{
	CurrentMathContainer = InMathContainer;
	return true;
}