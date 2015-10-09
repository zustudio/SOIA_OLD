
#pragma once

#include "TMainTool.h"
#include "Thread.h"

#include "StdDialogue.h"

namespace Supervisor
{
	RCLASS(TConsole,TMainTool)
	class LIBIMPEXP TConsole : public TConsole_Base
	{
		RCLASS_BEGIN()

		TConsole();

		virtual void Main() override;


		RFUNCTION(cmd_exit)
			bool cmd_exit();

		RFUNCTION(cmd_echo)
			bool cmd_echo(const std::string& InText);


	private:
		bool bExit;
		Env::StdDialogue MainDialogue;

		RCLASS_END()
	};
}
