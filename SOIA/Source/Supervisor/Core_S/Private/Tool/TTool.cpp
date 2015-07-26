
#include "TTool.h"
using namespace Supervisor;
using namespace Environment;

#include "RContainer.h"

TTool::TTool()
	: BaseType(),
	Dialogue(RPointer<RWrapper<DialogueInterface>>(nullptr)),
	GuiClass(nullptr)
{
	ReflectAttributes();
}

bool TTool::cmd_help()
{
	Dialogue->WriteLine("Help for Tool: in case you need help, please type help followed by command.");

	auto elementwrapper = RPointer<RElement>(nullptr);
	
	return true;
}
