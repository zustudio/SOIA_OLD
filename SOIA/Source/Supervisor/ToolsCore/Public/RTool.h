
#pragma once
#include "Definitions.h"

#include "RElement.h"
#include "RContainer.h"
#include "Function.h"
#include "DialogueInterface.h"



namespace Supervisor
{

	RABSTRACTCLASS(RTool,Environment::RElement)
	class LIBIMPEXP RTool : public RTool_Base
	{
		RCLASS_BEGIN();
		RTool(Environment::DialogueInterface* InDialogue);

		RPROPERTY(SomeInt);
		int SomeInt;
		
		RPROPERTY(FloatingOn);
		std::vector<float> FloatingOn;

		RFUNCTION(cmd_Help);
		bool cmd_Help();

		Environment::DialogueInterface* Dialogue;

		RCLASS_END();
	};
}
