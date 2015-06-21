
#pragma once

#include "RWorkerTool.h"

namespace Supervisor
{
	RCLASS(ConsoleWorker,RWorkerTool)
	class LIBIMPEXP ConsoleWorker : public ConsoleWorker_Base
	{
		RCLASS_BEGIN();

		ConsoleWorker(const RPointer<RDialogue>& InDialogue = nullptr);

		virtual void Main() override;
		bool ExecuteCommands(const std::string& InInput, std::vector<Environment::VoidPointer>& OutArguments);
		bool ExecuteCommand(const std::string& InTarget, std::string& InCommand, std::vector<Environment::VoidPointer>& InOutArguments);

		RFUNCTION(cmd_exit);
		bool cmd_exit();

		RFUNCTION(cmd_echo);
		bool cmd_echo(const std::string& InText);


	private:
		bool bExit;

		RCLASS_END();
	};
}
