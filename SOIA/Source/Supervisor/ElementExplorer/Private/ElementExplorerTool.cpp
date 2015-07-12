
#include "Definitions.h"

#include "ElementExplorerTool.h"
using namespace Supervisor;
using namespace Environment;

ElementExplorerTool::ElementExplorerTool(const RPointer<RDialogue>& InDialogue)
	: BaseType(InDialogue),
	CurrentContainer(nullptr)
{
	ReflectAttributes();
}

bool ElementExplorerTool::cmd_elem(RElement*& OutElement, const std::string& InName)
{
	if (!CurrentContainer)
		CurrentContainer = Container;

	OutElement = CurrentContainer->GetElement<RElement>(InName);
	if (OutElement)
		return true;
	else
		return false;
}

bool ElementExplorerTool::cmd_pwd(Environment::RContainer*& OutContainer)
{
	if (!CurrentContainer)
		CurrentContainer = Container;

	Dialogue->WriteLine(GetCurrentPath());
	OutContainer = CurrentContainer;
	return true;
}

bool ElementExplorerTool::cmd_ls()
{
	if (!CurrentContainer)
		CurrentContainer = Container;

	std::vector<RElement*> allElements = CurrentContainer->GetAllElements<RElement>();
	for (auto element : allElements)
	{
		std::string postfix;
		if (element->GetClass() == RContainer::StaticClass())
			postfix = "/";

		Dialogue->Write(element->GetID().Name + postfix + "  ");
	}
	Dialogue->WriteLine("");
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

	
	if (!result)
		Dialogue->WriteLine("Could not find path.");

	return result;
}

bool ElementExplorerTool::cmd_listattributes(RElement* const & InElementName, std::string const & InAttributeName)
{
	bool result = false;
	if (InElementName)
	{
		if (InAttributeName == "")
		{
			auto attributeNames = InElementName->GetAttributeNames();
			for (auto attributeName : attributeNames)
			{
				auto attribute = InElementName->GetAttribute(attributeName);
				Dialogue->WriteLine(attributeName + " \t(" + attribute.GetTypeID().ToEasyString() + ")");
			}
			result = true;
		}
		else
		{
			auto attribute = InElementName->GetAttribute(InAttributeName);
			if (!attribute.IsNullPointer())
			{
				// try to convert 
				auto converter = GetAtomReflectionProvider()->GetReflection(attribute.GetTypeID());
				std::string value;
				if (converter)
				{
					value = converter->ObjectToString(attribute);
				}
				else
				{
					value = "<No Reflection.>";
				}

				// get arguments if functioninterface
				std::string argumentTypes;
				if (attribute.GetTypeID().Decay() == TypeID::FromType<RFunction*>())
				{
					RFunction* function = attribute.CastAndDereference<RFunction*>();
					auto v_argumentTypes = function->GetArgumentTypes();
					for (auto argumentType : v_argumentTypes)
					{
						argumentTypes += std::string("\n\t") + (argumentType.IsConst() ? "IN" : "OUT") + "\t" + argumentType.ToEasyString();
					}
				}

				// write it out
				Dialogue->WriteLine("Type: \n\t\t" + attribute.GetTypeID().ToEasyString());
				if (argumentTypes == "")
					Dialogue->WriteLine("Value: \t" + value);
				else
					Dialogue->WriteLine("Args: \t" + argumentTypes);
			}
			else
			{
				Dialogue->WriteLine("Could not find attribute named '" + InAttributeName + "'.");
			}
		}
	}
	else
	{
		Dialogue->WriteLine("Could not find element.");
	}
	return result;
}

bool ElementExplorerTool::cmd_func(RFunction *& OutFunction, RElement * const & InElement, std::string const & InFuncName)
{
	auto p_Func = InElement->GetAttribute(InFuncName);
	OutFunction = p_Func.CastAndDereference<RFunction*>();

	Dialogue->WriteLine("Found function: " + InFuncName);
	return true;
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
