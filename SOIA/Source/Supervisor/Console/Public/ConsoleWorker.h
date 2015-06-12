
#pragma once

#include "RWorkerTool.h"

namespace Supervisor
{
	RCLASS(ConsoleWorker,RWorkerTool)
	class LIBIMPEXP ConsoleWorker : public ConsoleWorker_Base
	{
	public:
		ConsoleWorker(DialogueInterface* InDialogue = nullptr);

		virtual void Main() override;

	private:
		bool bExit;
	};
}