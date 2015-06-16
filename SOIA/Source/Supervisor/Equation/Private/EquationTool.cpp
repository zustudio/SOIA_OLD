
#include "Definitions.h"

#include "EquationTool.h"
using namespace Supervisor;
using namespace Environment;

REquationTool::REquationTool(DialogueInterface* InDialogue)
	: BaseType(InDialogue),
	CurrentMathContainer(nullptr)
{
	ReflectAttributes();
}