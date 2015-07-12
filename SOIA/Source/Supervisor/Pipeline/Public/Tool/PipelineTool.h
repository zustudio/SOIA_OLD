
#pragma once

#include "RTool.h"

#include "Pipe.h"

namespace Supervisor
{
	RCLASS(PipelineTool,RTool)
	class LIBIMPEXP PipelineTool : public PipelineTool_Base
	{
		RCLASS_BEGIN();

		PipelineTool(const Environment::RPointer<RDialogue>& InDialogue = Environment::RPointer<RDialogue>(nullptr));

		RFUNCTION(cmd_listpipes)
			bool cmd_listpipes();

		RFUNCTION(cmd_pipe)
			bool cmd_pipe(Pipe* & OutPipe, const std::string& InName);

		RFUNCTION(cmd_add)
			bool cmd_add(Environment::RFunction* const &InFunction);

		RFUNCTION(cmd_link)
			bool cmd_link(Pipe* const& OutPipe, int const& OutArgNum, Pipe* const& InPipe, int const& InArgNum);

		RFUNCTION(cmd_execute)
			bool cmd_execute(int const& Number);

		std::vector<Pipe*> Pipes;

		OutPort PipeStart;
		InPort PipeEnd;

		RCLASS_END();
	};
}