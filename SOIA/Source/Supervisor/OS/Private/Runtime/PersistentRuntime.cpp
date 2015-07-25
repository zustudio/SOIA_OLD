
#include "Definitions.h"

#include "PersistentRuntime.h"
using namespace Supervisor;


////////////////////////////////////////////////////////////////
// Public Main Entry Point
void PersistentRuntime::Run(RClass* InStandardDialogueClass)
{
	InitializeElementHierarchy(InStandardDialogueClass);
	RegisterReflectedClasses();
	RunTool();
}

////////////////////////////////////////////////////////////////
// Executed sub steps
void PersistentRuntime::InitializeElementHierarchy(RClass* InStandardDialogueClass)
{
	RWrapperInterface* p_dialogue = dynamic_cast<RWrapperInterface*>(InStandardDialogueClass->GetDefaultObject());
	RWrapper<DialogueInterface> dialogue = p_dialogue;
	dialogue->WriteLine("Dialogue loaded");
}

void PersistentRuntime::RegisterReflectedClasses()
{
}

void PersistentRuntime::RunTool()
{
}
