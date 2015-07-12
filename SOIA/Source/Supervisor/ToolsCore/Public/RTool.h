
#pragma once
#include "Definitions.h"

#include "RElement.h"
#include "RContainer.h"
#include "Function.h"
#include "RDialogue.h"
#include "RPointer.h"


namespace Supervisor
{

	RABSTRACTCLASS(RTool,Environment::RElement)
	class LIBIMPEXP RTool : public RTool_Base
	{
		RCLASS_BEGIN();
			RTool(const Environment::RPointer<RDialogue>& InDialogue);

		RFUNCTION(cmd_help);
			bool cmd_help();

		RPROPERTY(Dialogue)
			Environment::RPointer<RDialogue> Dialogue;

		RPROPERTY(GuiClass)
			Environment::RClass* GuiClass;

		RCLASS_END();
	};
}
