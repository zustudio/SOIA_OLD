
#include "Definitions.h"

#include "ElementExplorerTool.h"
using namespace Supervisor;

ElementExplorerTool::ElementExplorerTool(DialogueInterface* InDialogue)
	: BaseType(InDialogue),
	CurrentContainer(nullptr)
{
	ReflectAttributes();
}

bool ElementExplorerTool::cmd_ls()
{
	if (!CurrentContainer)
		CurrentContainer = Container;

	Dialogue->WriteLine("Current path:");
	Dialogue->WriteLine("\t" + GetCurrentPath());
	Dialogue->WriteLine("Current elements:");

	std::vector<RElement*> allElements = CurrentContainer->GetAllElements<RElement>();
	for (auto element : allElements)
	{
		std::string prefix;
		if (element->GetClass() == RContainer::StaticClass())
			prefix = "/";

		Dialogue->WriteLine("\t" + element->GetClass()->GetType().ToString() + '\t' + prefix + element->GetID().Name);
	}
	return true;
}

bool ElementExplorerTool::cmd_cc(const std::string& InContainerName)
{
	bool result = false;
	if (InContainerName == "..")
	{
		CurrentContainer = Container->GetContainer();
		result = true;
	}
	else
	{
		RContainer* newContainer = CurrentContainer->GetElement<RContainer>(InContainerName);
		if (newContainer)
		{
			CurrentContainer = newContainer;
			result = true;
		}
	}

	if (result)
		Dialogue->WriteLine("New path: " + GetCurrentPath());
	else
		Dialogue->WriteLine("Could not find path.");

	return result;
}

std::string ElementExplorerTool::GetCurrentPath()
{
	RContainer* current = nullptr;
	RContainer* next = CurrentContainer;
	std::string result;

	do
	{
		current = next;
		next = next->GetContainer();
		if (next == current) { next = nullptr; }
		result = current->GetID().Name + "/" + result;
	} while (next);

	return result;
}