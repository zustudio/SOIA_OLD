
#include "Definitions.h"
#include "TextBoxDialogue.h"
using namespace Env;

#include <thread>
using namespace std::chrono_literals;

TextBoxDialogue::TextBoxDialogue(TextBox & InInputBox, TextBox & InOutputBox)
	:
	InputBox(InInputBox),
	OutputBox(InOutputBox)
{}

void TextBoxDialogue::Write(const std::string & InText)
{
	std::string text = OutputBox.GetText() + InText;
	OutputBox.SetText(text);
}

void TextBoxDialogue::WriteLine(const std::string & InText)
{
	std::string text = OutputBox.GetText() + InText + '\n';
	OutputBox.SetText(text);
}

void TextBoxDialogue::GetNextLine(std::string & OutText)
{
	InputBox.SetText("");
	std::string const & text = InputBox.GetText();
	while (!text.size() || text.back() != '\n')
	{
		std::this_thread::sleep_for(100ms);
	}
	OutText = InputBox.GetText();
}

