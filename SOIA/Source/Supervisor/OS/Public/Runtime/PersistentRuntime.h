
#pragma once

#include "DialogueInterface.h"
using namespace Environment;

#include "RClass.h"
#include "RWrapper.h"
#include "RElement.h"
#include "RContainer.h"

#include "TConsole.h"
#include "TRuntime.h"
#include "TElementExplorer.h"

namespace Supervisor
{
	class LIBIMPEXP PersistentRuntime
	{
	public:
		static void Initialize(RClass* InStandardDialogueClass);
		static void Start();
		static void ChangeMainTool(TMainTool* InTool);
	private:
		////////////////////////////////////////////////////////////////
		// run chain
		static void InitializeGlobalObjects(RClass* InStandardDialogueClass);
		static void InitializeElementHierarchy();
		static void RegisterReflectedClasses();

		////////////////////////////////////////////////////////////////
		// global objects
		static RContainer* GlobalContainer;

		static TMainTool* CurrentMainTool;
		static TRuntime* RuntimeTool;
		static TElementExplorer* ExplorerTool;

		////////////////////////////////////////////////////////////////
		// information passing between threads
		static TMainTool* NextMainTool;
	};
}
