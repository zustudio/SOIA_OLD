
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

RContainer* PersistentRuntime::GlobalContainer = nullptr;
TRuntime* PersistentRuntime::RuntimeTool = nullptr;
TElementExplorer* PersistentRuntime::ExplorerTool = nullptr;
TMainTool* PersistentRuntime::CurrentMainTool = nullptr;
TMainTool* PersistentRuntime::NextMainTool = nullptr;

////////////////////////////////////////////////////////////////
// Public Main Entry Point
void PersistentRuntime::Initialize(RClass* InStandardDialogueClass)
{
	InitializeGlobalObjects(InStandardDialogueClass);
	InitializeElementHierarchy();
	RegisterReflectedClasses();
}

void PersistentRuntime::Start()
{
	do
	{
		CurrentMainTool = NextMainTool;
		CurrentMainTool->Start();
		CurrentMainTool->Join();
	} while (NextMainTool);
}

void PersistentRuntime::ChangeMainTool(TMainTool* InTool)
{
	NextMainTool = InTool;
	CurrentMainTool->Stop();
}

////////////////////////////////////////////////////////////////
// Executed sub steps
void PersistentRuntime::InitializeGlobalObjects(RClass* InStandardDialogueClass)
{
	LOGSTATUS("Initializing global objects... ");

	// start global render thread
	GlobalRenderThread()->Start();

	LOGSTATUS("Done.");
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

	// add predefined tools
	NextMainTool = new TConsole();
	RuntimeTool = new TRuntime();
	ExplorerTool = new TElementExplorer();
	GlobalContainer->Register(NextMainTool, "console");
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
