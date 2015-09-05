
#include "Definitions.h"

#include "EquationTool.h"
using namespace Supervisor;
using namespace Environment;


REquationTool::REquationTool()
	: BaseType(),
	CurrentMathContainer(nullptr)
{
	ReflectAttributes();
}

bool REquationTool::cmd_calc(const std::string& InEqName, const double& Argument)
{
	bool success = false;
	double OutResult;
	if (pipe_calculate2d(Argument, OutResult))
	{
		Dialogue->WriteLine(" =" + std::to_string(OutResult));
		success = true;
	}
	return success;
}

bool REquationTool::cmd_storeeq(const std::string& InString)
{
	bool result = false;
	if (CurrentMathContainer)
	{
		Equations.push_back(CurrentMathContainer->ParseString(InString));
		result = true;
	}
	return result;
}

bool REquationTool::cmd_setmathcontainer(MathContainer* const & InMathContainer)
{
	CurrentMathContainer = InMathContainer;
	return true;
}

bool REquationTool::pipe_calculate2d(double const & InX, double & OutY)
{
	bool success = false;
	if (CurrentMathContainer)
	{
		if(Equations.size())
		{
			double result = Equations[0]->Execute({ InX });
			success = true;
		}
	}
	return success;
}
