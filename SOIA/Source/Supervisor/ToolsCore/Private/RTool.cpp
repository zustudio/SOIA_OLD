
#include "RTool.h"
using namespace Supervisor;
using namespace Environment;

#include "RContainer.h"

RTool::RTool(DialogueInterface* InDialogue)
	: BaseType(),
	Dialogue(InDialogue)
{
	ReflectAttributes();
}

bool RTool::cmd_Help()
{
	Dialogue->WriteLine("Help for Tool: in case you need help, please type help followed by command.");
	return true;
}
