
#pragma once

#include "RTool.h"

#include "MathContainer.h"
#include "D1D1GenericFunction.h"

namespace Supervisor
{
	RCLASS(REquationTool,RTool)
	class LIBIMPEXP REquationTool : public REquationTool_Base
	{
		RCLASS_BEGIN();
		////////////////////////////////////////////////////////////////
		// Functions

		//----- ctor -----
		REquationTool(const Environment::RPointer<RDialogue>& InDialogue = Environment::RPointer<RDialogue>(nullptr));

		//----- commands -----
		RFUNCTION(cmd_calc)
			bool cmd_calc(const std::string& InEqName, const double& Argument);

		RFUNCTION(cmd_storeeq)
			bool cmd_storeeq(const std::string& InEquationString);
		
		RFUNCTION(cmd_setmathcontainer)
			bool cmd_setmathcontainer(Environment::MathContainer* const & InMathContainer);

		//----- pipes -----
		RFUNCTION(pipe_calculate2d)
			bool pipe_calculate2d(double const& InX, double& OutY);

		////////////////////////////////////////////////////////////////
		// Variables

		RPROPERTY(CurrentMathContainer)
			Environment::MathContainer* CurrentMathContainer;

		RPROPERTY(Equations)
			std::vector<Environment::D1D1GenericFunction> Equations;

		RCLASS_END();
	};
}
