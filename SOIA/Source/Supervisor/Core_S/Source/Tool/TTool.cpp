
#include "TTool.h"
using namespace Supervisor;
using namespace Environment;

#include "RContainer.h"

TTool::TTool()
	: BaseType(),
	Dialogue(nullptr)
{
	ReflectAttributes();
}

bool TTool::cmd_help()
{
	Dialogue->WriteLine("Help for Tool: in case you need help, please type help followed by command.");

	auto elementwrapper = RPointer<RElement>(nullptr);
	
	return true;
}

void TTool::SetDialogue(Env::DialogueInterface * InDialogue)
{
	Dialogue = InDialogue;
}