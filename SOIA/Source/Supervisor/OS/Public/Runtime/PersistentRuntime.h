
#pragma once

#include "DialogueInterface.h"
using namespace Environment;

#include "RClass.h"
#include "RWrapper.h"
#include "RElement.h"
#include "RContainer.h"

#include "TConsole.h"
#include "TRuntime.h"
#include "ElementExplorerTool.h"

namespace Supervisor
{
	class LIBIMPEXP PersistentRuntime
	{
	public:
		static void Initialize(RClass* InStandardDialogueClass);
		static void Run();
	private:
		////////////////////////////////////////////////////////////////
		// run chain
		static void InitializeGlobalObjects(RClass* InStandardDialogueClass);
		static void InitializeElementHierarchy();
		static void RegisterReflectedClasses();
		static void RunTool();

		////////////////////////////////////////////////////////////////
		// global objects
		static RWrapper<DialogueInterface> GlobalDialogue;
		static RContainer* GlobalContainer;

		static TConsole* ConsoleTool;
		static TRuntime* RuntimeTool;
		static ElementExplorerTool* ExplorerTool;
	};
}