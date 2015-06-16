
#pragma once

#include "RTool.h"

namespace Supervisor
{
	RCLASS(PipeTool,RTool)
	class PipeTool : PipeTool_Base
	{
		RCLASS_BEGIN();

		PipeTool(DialogueInterface* InDialogue = nullptr);

		RFUNCTION(cmd_add)
			bool cmd_add();

		RCLASS_END();
	};
}