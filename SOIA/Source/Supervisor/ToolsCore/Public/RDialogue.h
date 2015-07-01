
#pragma once

#include "RElement.h"

#include "DialogueInterface.h"

namespace Supervisor
{
	RCLASS(RDialogue, Environment::RElement);
	class LIBIMPEXP RDialogue : public RDialogue_Base, public DialogueInterface
	{
		RCLASS_BEGIN();

		////////////////////////////////////////////////////////////////////
		// Functions

		//----- init -----

		/// ctor
		RDialogue(Environment::DialogueInterface* InDialogue = nullptr);

		//----- access forwarding -----

		virtual void Write(const std::string& InText) override;
		virtual void WriteLine(const std::string& InText) override;
		virtual void GetNextLine(std::string& OutText) override;
	
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