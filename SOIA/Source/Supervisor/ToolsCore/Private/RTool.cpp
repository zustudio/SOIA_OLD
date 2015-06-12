
#include "RTool.h"
using namespace Supervisor;
using namespace Environment;

RTool::RTool(DialogueInterface* InDialogue)
	: BaseType(),
	Dialogue(InDialogue)
{
	RegisterAllObjects();
}

bool RTool::cmd_Help()
{
	Dialogue->WriteLine("Help for Tool: in case you need help, please type help followed by command.");
	return true;
}
