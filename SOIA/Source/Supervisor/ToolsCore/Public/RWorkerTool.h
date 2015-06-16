
#pragma once

#include "RTool.h"
#include "Thread.h"

namespace Supervisor
{
	RABSTRACTCLASS(RWorkerTool, RTool)
	class LIBIMPEXP RWorkerTool : public RWorkerTool_Base, public Environment::Thread
	{
	public:
		RWorkerTool(Environment::DialogueInterface* InDialogue);
	};
}
