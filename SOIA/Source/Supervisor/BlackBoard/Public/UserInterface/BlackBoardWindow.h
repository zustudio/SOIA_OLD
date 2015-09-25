
#pragma once

#include "ControlWindow.h"

#include "TextBox.h"
#include "TextBoxDialogue.h"

namespace Supervisor
{
	class BlackBoardWindow : public Env::ControlWindow
	{
	public:
		///\name ctor
		///\{
			BlackBoardWindow();
		///\}

		///\name access
		///\{
			Env::DialogueInterface* GetDialogue();
		///\}

	private:
		///\name abstractions
		///\{
			Env::TextBoxDialogue Dialogue;
		///\}

		///\name controls
		///\{
			Env::TextBox MainLog;
			Env::TextBox MainInput;
		///\}

	};
}