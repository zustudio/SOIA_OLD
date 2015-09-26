
#include "Definitions.h"

#include "PersistentRuntime.h"
using namespace Environment;
using namespace Supervisor;

#include "GlobalLogger.h"
#include "GlobalContainer.h"
#include "GlobalRenderThread.h"

//classes to be registered
#include "TCalculator.h"
#include "RGraphTool2D.h"
#include "PipelineTool.h"
#include "RConversionPipes.h"
#include "TBlackBoard.h"

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

	// start global render thread
	GlobalRenderThread()->Start();

	std::cout << "Done." << std::endl;
}

void PersistentRuntime::InitializeElementHierarchy()
{
	LOGSTATUS("Initializing element hierarchy... ");
	// create global top container
	GlobalContainer = new RContainer(Range<int>(0, 10));
	GlobalContainer->GetName() = "Global";
	SetGlobalContainer(GlobalContainer);

	// add sub container
	GlobalContainer->Register(new RContainer(Range<int>(11, 100)), "Project");
	GlobalContainer->Register(new RContainer(Range<int>(11,100)), "Temp");
	
	// register dialogue
	GlobalContainer->Register(&GlobalDialogue, "GlobalDialogue");

	// add predefined tools
	ConsoleTool = new TConsole();
	RuntimeTool = new TRuntime();
	ExplorerTool = new TElementExplorer();
	GlobalContainer->Register(ConsoleTool, "console");
	GlobalContainer->Register(RuntimeTool, "runtime");
	GlobalContainer->Register(ExplorerTool, "explorer");

	LOGSTATUS("Done.");
}

void PersistentRuntime::RegisterReflectedClasses()
{
	LOGSTATUS("Registering reflected classes...");
	GlobalRClassProvider()->RegisterList<
		TCalculator,
		RGraphTool,
		PipelineTool,
		RConversionPipes,
		TBlackBoard>();
	LOGSTATUS("Done.");
}

void PersistentRuntime::RunTool()
{
	LOGSTATUS("Running global runtime tool... ");
	RuntimeTool->Run();
}