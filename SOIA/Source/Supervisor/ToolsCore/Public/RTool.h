
#pragma once
#include "Definitions.h"

#include "RElement.h"
#include "RContainer.h"
#include "Function.h"
#include "RDialogue.h"
#include "RTypedPointer.h"


namespace Supervisor
{

	RABSTRACTCLASS(RTool,Environment::RElement)
	class LIBIMPEXP RTool : public RTool_Base
	{
		RCLASS_BEGIN();
			RTool(const RTypedPointer<RDialogue>& InDialogue);

		RFUNCTION(cmd_help);
			bool cmd_help();

		RPROPERTY(Dialogue)
			RTypedPointer<RDialogue> Dialogue;

		RCLASS_END();
	};
}
