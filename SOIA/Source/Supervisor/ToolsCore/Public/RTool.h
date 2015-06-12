
#pragma once
#include "Definitions.h"

#include "RElement.h"
#include "Function.h"
#include "DialogueInterface.h"
#include "ConstExprDynamicList.h"



namespace Supervisor
{

	RABSTRACTCLASS(RTool,Environment::RElement)
	class LIBIMPEXP RTool : public RTool_Base
	{
		RCLASS_START();
		RTool(DialogueInterface* InDialogue);

		RPROPERTY(SomeInt);
		int SomeInt;
		
		RPROPERTY(FloatingOn);
		std::vector<float> FloatingOn;

		RFUNCTION(cmd_Help);
		bool cmd_Help();

	protected:
		DialogueInterface* Dialogue;

		RCLASS_END();
	};
}