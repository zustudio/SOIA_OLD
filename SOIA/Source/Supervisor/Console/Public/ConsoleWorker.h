
#pragma once

#include "RWorkerTool.h"

#include "Tokenizer.h"

namespace Supervisor
{
	RCLASS(ConsoleWorker,RWorkerTool)
	class LIBIMPEXP ConsoleWorker : public ConsoleWorker_Base
	{
		RCLASS_BEGIN();

		ConsoleWorker(const Environment::RPointer<RDialogue>& InDialogue = Environment::RPointer<RDialogue>(nullptr));

		virtual void Main() override;
		bool ExecuteCommands(Token*, std::vector<Environment::VoidPointer>& OutArguments);
		bool ExecuteCommand(const std::string& InTarget, std::string& InCommand, std::vector<Environment::VoidPointer>& InOutArguments);

		std::vector<std::string> GetArguments(const std::string& Input);

		RFUNCTION(cmd_exit);
		bool cmd_exit();

		RFUNCTION(cmd_echo);
		bool cmd_echo(const std::string& InText);


	private:
		bool bExit;
		Tokenizer InputTokenizer;

		RCLASS_END();
	};
}
