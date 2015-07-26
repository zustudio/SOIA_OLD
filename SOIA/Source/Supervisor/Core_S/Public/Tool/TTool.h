
#pragma once
#include "Definitions.h"

#include "RElement.h"
#include "RContainer.h"
#include "Function.h"
#include "DialogueInterface.h"
#include "RPointer.h"
#include "RWrapper.h"


namespace Supervisor
{

	RABSTRACTCLASS(TTool,Environment::RElement)
	class LIBIMPEXP TTool : public TTool_Base
	{
		RCLASS_BEGIN()
			TTool();

		RFUNCTION(cmd_help)
			bool cmd_help();

		RPROPERTY(Dialogue)
			Environment::RPointer<Environment::RWrapper<Environment::DialogueInterface>> Dialogue;

		Environment::RClass* GuiClass;

		RCLASS_END()
	};
}
