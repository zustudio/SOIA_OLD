
#pragma once

#include "Definitions.h"

#include "Workspace.h"
using namespace Supervisor;

#include "RContainer.h"
#include "ConsoleWorker.h"
#include "ElementExplorerTool.h"
#include "ContainerProvider.h"
using namespace Environment;

void Workspace::Initialize(RDialogue& InStandardDialogue)
{
	// create top level container
	RContainer* topContainer = new RContainer(Range<int>(0, 10));
	SetTopContainer(topContainer);

	// create top level tools
	ConsoleWorker* Console = new ConsoleWorker(RPointer<RDialogue>(&InStandardDialogue));
	topContainer->Register(Console, "console");
	ElementExplorerTool* elementexplorer = new ElementExplorerTool(RPointer<RDialogue>(&InStandardDialogue));
	topContainer->Register(elementexplorer, "elementexplorer");

}
