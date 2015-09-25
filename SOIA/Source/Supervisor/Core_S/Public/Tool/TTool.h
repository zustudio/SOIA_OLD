
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

	public:
		///\name ctor
		///\{
			TTool();
		///\}

		RFUNCTION(cmd_help)
			bool cmd_help();

		///\name configuration
		///\{
			void SetDialogue(Env::DialogueInterface* InDialogue);
		///\}

	protected:
		Env::DialogueInterface* Dialogue;

		RCLASS_END()
	};
}
