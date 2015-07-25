
#pragma once

#include "DialogueInterface.h"
using namespace Environment;

#include "RClass.h"
#include "RElement.h"
#include "RWrapper.h"

namespace Supervisor
{
	class LIBIMPEXP PersistentRuntime
	{
	public:
		static void Run(RClass* InStandardDialogueClass);
	private:
		static void InitializeElementHierarchy(RClass* InStandardDialogueClass);
		static void RegisterReflectedClasses();
		static void RunTool();
	};
}