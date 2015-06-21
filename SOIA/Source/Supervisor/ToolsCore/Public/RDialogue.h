
#pragma once

#include "RElement.h"

#include "DialogueInterface.h"

namespace Supervisor
{
	RCLASS(RDialogue, Environment::RElement);
	class LIBIMPEXP RDialogue : public RDialogue_Base
	{
		RCLASS_BEGIN();

		////////////////////////////////////////////////////////////////////
		// Functions

		//----- init -----

		/// ctor
		RDialogue(Environment::DialogueInterface* InDialogue = nullptr);

		//----- access forwarding -----

		/// Returns the dialogue interface this object points to.
		Environment::DialogueInterface* operator->();
	
		/// Returns the dialogue interface this object points to.
		Environment::DialogueInterface* GetDialogueInterface();

	private:
		///////////////////////////////////////////////////////////////////
		// Variables

		/// The dialogue interface this object points to.
		Environment::DialogueInterface* Dialogue;

		RCLASS_END();
	};
}