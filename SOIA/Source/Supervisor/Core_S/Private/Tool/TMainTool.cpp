
#include "Definitions.h"

#include "TMainTool.h"
using namespace Env;
using namespace Sup;

#include "GlobalLogger.h"

TMainTool::TMainTool()
	: BaseType()
{

}

void TMainTool::ConfigureMainTool(DialogueInterface * InDialogue)
{
	auto tools = Container->GetAllElements<TTool>();
	for (TTool* tool : tools)
	{
		tool->SetDialogue(InDialogue);
	}

	GlobalLogger()->SetDialogue(InDialogue);
}
