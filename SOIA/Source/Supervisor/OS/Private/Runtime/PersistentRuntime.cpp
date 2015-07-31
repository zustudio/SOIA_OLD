
#include "Definitions.h"

#include "PersistentRuntime.h"
using namespace Environment;
using namespace Supervisor;

#include "LogProvider.h"
#include "ContainerProvider.h"

#include <iostream>

RWrapper<DialogueInterface> PersistentRuntime::GlobalDialogue = RWrapper<DialogueInterface>();
RContainer* PersistentRuntime::GlobalContainer = nullptr;
TConsole* PersistentRuntime::ConsoleTool = nullptr;
TRuntime* PersistentRuntime::RuntimeTool = nullptr;
TElementExplorer* PersistentRuntime::ExplorerTool = nullptr;

////////////////////////////////////////////////////////////////
// Public Main Entry Point
void PersistentRuntime::Initialize(RClass* InStandardDialogueClass)
{
	InitializeGlobalObjects(InStandardDialogueClass);
	InitializeElementHierarchy();
	RegisterReflectedClasses();
}

void PersistentRuntime::Run()
{
	RunTool();
}

////////////////////////////////////////////////////////////////
// Executed sub steps
void PersistentRuntime::InitializeGlobalObjects(RClass* InStandardDialogueClass)
{
	std::cout << "Initializing global objects... ";

	// create global main dialogue from class
	GlobalDialogue = dynamic_cast<RWrapperInterface*>(InStandardDialogueClass->GetDefaultObject());

	// create global logger
	Logger globalLogger = Logger(*GlobalDialogue);
	SetGlobalLogger(globalLogger);

	std::cout << "Done." << std::endl;
}

void PersistentRuntime::InitializeElementHierarchy()
{
	LOGSTATUS("Initializing element hierarchy... ");
	// create global top container
	GlobalContainer = new RContainer(Range<int>(0, 10));
	GlobalContainer->GetID().Name = "Global";
	SetGlobalContainer(GlobalContainer);
	
	// add sub container
	GlobalContainer->Register(new RContainer(Range<int>(11, 100)), "Project");
	GlobalContainer->Register(new RContainer(Range<int>(11,100)), "Temp");

	// add predefined tools
	ConsoleTool = new TConsole();
	RuntimeTool = new TRuntime();
	ExplorerTool = new TElementExplorer();
	ConsoleTool->Dialogue = &GlobalDialogue;
	RuntimeTool->Dialogue = &GlobalDialogue;
	ExplorerTool->Dialogue = &GlobalDialogue;
	GlobalContainer->Register(ConsoleTool, "console");
	GlobalContainer->Register(RuntimeTool, "runtime");
	GlobalContainer->Register(ExplorerTool, "explorer");

	LOGSTATUS("Done.");
}

void PersistentRuntime::RegisterReflectedClasses()
{
}

void PersistentRuntime::RunTool()
{
	LOGSTATUS("Running global runtime tool... ");
	RuntimeTool->Run();
}
