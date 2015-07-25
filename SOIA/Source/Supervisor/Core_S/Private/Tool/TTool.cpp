
#include "TTool.h"
using namespace Supervisor;
using namespace Environment;

#include "RContainer.h"

TTool::TTool(const RPointer<RDialogue>& InDialogue)
	: BaseType(),
	Dialogue(InDialogue),
	GuiClass(nullptr)
{
	ReflectAttributes();
}

bool TTool::cmd_help()
{
	Dialogue.Resolve()->GetDialogueInterface()->WriteLine("Help for Tool: in case you need help, please type help followed by command.");
	return true;
}
