
#pragma once

#include "RTool.h"

#include "MathContainer.h"

namespace Supervisor
{
	RCLASS(REquationTool,RTool)
	class REquationTool : public REquationTool_Base
	{
		RCLASS_BEGIN();
		////////////////////////////////////////////////////////////////
		// Functions

		//----- ctor -----
		REquationTool(DialogueInterface* InDialogue);

		//----- commands -----
		RFUNCTION(cmd_create)
			bool cmd_create(const std::string& InEquationString);

		RFUNCTION(cmd_setmathcontainer)
			bool cmd_setmathcontainer(const std::string& InContainerPath);

		////////////////////////////////////////////////////////////////
		// Variables

		RPROPERTY(CurrentMathContainer)
			MathContainer* CurrentMathContainer;

		RCLASS_END();
	};
}