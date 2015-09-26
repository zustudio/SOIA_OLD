
#pragma once

#include "DialogueInterface.h"

#include "TextBox.h"

namespace Environment
{
	class LIBIMPEXP TextBoxDialogue : public DialogueInterface
	{
	public:
		TextBoxDialogue(TextBox & InInputBox, TextBox & InOutputBox);

		virtual void Write(const std::string& InText) override;
		virtual void WriteLine(const std::string& InText) override;
		virtual void GetNextLine(std::string& OutText) override;

	private:
		TextBox& InputBox;
		TextBox& OutputBox;
	};
}