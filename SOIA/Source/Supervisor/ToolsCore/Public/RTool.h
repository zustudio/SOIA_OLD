
#pragma once
#include "Definitions.h"

#include "RElement.h"
#include "Function.h"

#include "DialogueInterface.h"

namespace Supervisor
{
	RCLASS(RTool,Environment::RElement)
	class LIBIMPEXP RTool : public RTool_Base
	{
	public:
		RTool(DialogueInterface* InDialogue = nullptr);


		bool cmd_Help();
		Environment::FunctionInterface* cmd_Help_Interface = new Function<RTool>(this, &RTool::cmd_Help);

	private:
		DialogueInterface* Dialogue;
	};
}