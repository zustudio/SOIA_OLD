
#include "Definitions.h"

#include "RDialogue.h"
using namespace Environment;
using namespace Supervisor;

RDialogue::RDialogue(DialogueInterface* InDialogue)
	: BaseType(),
	Dialogue(InDialogue)
{ }

void RDialogue::Write(const std::string& InText)
{
	Dialogue->Write(InText);
}
void RDialogue::WriteLine(const std::string& InText)
{
	Dialogue->WriteLine(InText);
}
void RDialogue::GetNextLine(std::string& OutText)
{
	Dialogue->GetNextLine(OutText);
}

DialogueInterface* RDialogue::GetDialogueInterface()
{
	return Dialogue;
}