
#pragma once

#include "RTool.h"

namespace Supervisor
{
	RCLASS(PipelineTool,RTool)
	class PipelineTool : public PipelineTool_Base
	{
		RCLASS_BEGIN();

		PipelineTool(const Environment::RPointer<RDialogue>& InDialogue = RPointer<RDialogue>(nullptr));

		RFUNCTION(cmd_add)
			bool cmd_add();

		RCLASS_END();
	};
}