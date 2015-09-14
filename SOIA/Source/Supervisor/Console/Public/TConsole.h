
#pragma once

#include "TTool.h"
#include "Thread.h"

#include "Tokenizer.h"

namespace Supervisor
{
	RCLASS(TConsole,TTool)
	class LIBIMPEXP TConsole : public TConsole_Base, public Environment::Thread
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
		Environment::Tokenizer InputTokenizer;

		RCLASS_END()
	};
}
