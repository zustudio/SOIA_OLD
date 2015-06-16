
#pragma once

#include "RWorkerTool.h"

namespace Supervisor
{
	RCLASS(ConsoleWorker,RWorkerTool)
	class LIBIMPEXP ConsoleWorker : public ConsoleWorker_Base
	{
		RCLASS_BEGIN();

		ConsoleWorker(Environment::DialogueInterface* InDialogue = nullptr);

		virtual void Main() override;

		RFUNCTION(cmd_exit);
		bool cmd_exit();

		RFUNCTION(cmd_echo);
		bool cmd_echo(const std::string& InText);


	private:
		bool bExit;

		RCLASS_END();
	};
}
