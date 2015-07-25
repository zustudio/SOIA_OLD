
#pragma once
#include "Definitions.h"

#include "RElement.h"
#include "RContainer.h"
#include "Function.h"
#include "RDialogue.h"
#include "RPointer.h"


namespace Supervisor
{

	RABSTRACTCLASS(TTool,Environment::RElement)
	class LIBIMPEXP TTool : public TTool_Base
	{
		RCLASS_BEGIN()
			TTool(const Environment::RPointer<RDialogue>& InDialogue);

		RFUNCTION(cmd_help)
			bool cmd_help();

		RPROPERTY(Dialogue)
			Environment::RPointer<RDialogue> Dialogue;

		Environment::RClass* GuiClass;

		RCLASS_END()
	};
}
