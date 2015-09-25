
#pragma once

#include "TMainTool.h"
#include "Thread.h"

#include "Tokenizer.h"
#include "StdDialogue.h"

namespace Supervisor
{
	RCLASS(TConsole,TMainTool)
	class LIBIMPEXP TConsole : public TConsole_Base
	{
		RCLASS_BEGIN()

		TConsole();

		virtual void Main() override;
		bool ExecuteCommands(std::list<Environment::Token*> const & Input, std::vector<Environment::VoidPointer>& OutArguments);
		bool ExecuteCommand(const std::string& InTarget, std::string& InCommand, std::vector<Environment::VoidPointer>& InOutArguments);

		std::vector<std::string> GetArguments(const std::string& Input);

		RFUNCTION(cmd_exit)
			bool cmd_exit();

		RFUNCTION(cmd_echo)
			bool cmd_echo(const std::string& InText);


	private:
		bool bExit;
		Env::Tokenizer InputTokenizer;
		Env::StdDialogue MainDialogue;

		RCLASS_END()
	};
}
