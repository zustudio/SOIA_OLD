
#include "Definitions.h"

#include "RDialogue.h"
using namespace Environment;
using namespace Supervisor;

RDialogue::RDialogue(DialogueInterface* InDialogue)
	: BaseType(),
	Dialogue(InDialogue)
{ }

DialogueInterface* RDialogue::operator->()
{
	return Dialogue;
}

DialogueInterface* RDialogue::GetDialogueInterface()
{
	return Dialogue;
}