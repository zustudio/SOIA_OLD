
#pragma once

#include "TTool.h"

#include "MathContainer.h"

namespace Supervisor
{
	RCLASS(TCalculator,TTool)
	class LIBIMPEXP TCalculator : public TCalculator_Base
	{
		RCLASS_BEGIN()
		////////////////////////////////////////////////////////////////
		// Functions

		//----- ctor -----
		TCalculator();

		//----- commands -----
		RFUNCTION(cmd_calc)
			bool cmd_calc(const std::string& InEqName);

		//----- pipes -----
		RFUNCTION(pipe_calculate2d)
			bool pipe_calculate2d(std::string const & InFuncName, double const& InX, double& OutY);

		////////////////////////////////////////////////////////////////
		// Variables

		RPROPERTY(CurrentMathContainer)
			Environment::MathContainer* CurrentMathContainer;

		
		std::vector<DynamicMathFunction*> Functions;

		RCLASS_END()
	};
}
