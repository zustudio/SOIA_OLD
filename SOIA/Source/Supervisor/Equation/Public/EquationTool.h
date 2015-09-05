
#pragma once

#include "TTool.h"

#include "MathContainer.h"

namespace Supervisor
{
	RCLASS(REquationTool,TTool)
	class LIBIMPEXP REquationTool : public REquationTool_Base
	{
		RCLASS_BEGIN()
		////////////////////////////////////////////////////////////////
		// Functions

		//----- ctor -----
		REquationTool();

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

		
		std::vector<Environment::Function<double, std::vector<double> const &>*> Equations;

		RCLASS_END()
	};
}
