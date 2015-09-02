
#include "Definitions.h"

#include "TElementExplorer.h"
using namespace Supervisor;
using namespace Environment;

TElementExplorer::TElementExplorer()
	: BaseType(),
	CurrentContainer(nullptr)
{
	ReflectAttributes();
}

bool TElementExplorer::cmd_elem(RElement*& OutElement, const std::string& InName)
{
	if (!CurrentContainer)
		CurrentContainer = Container;

	OutElement = CurrentContainer->GetElement<RElement>(InName);
	if (OutElement)
		return true;
	else
		return false;
}

bool TElementExplorer::cmd_pwd(Environment::RContainer*& OutContainer)
{
	if (!CurrentContainer)
		CurrentContainer = Container;

	Dialogue->WriteLine(GetCurrentPath());
	OutContainer = CurrentContainer;
	return true;
}

bool TElementExplorer::cmd_ls()
{
	if (!CurrentContainer)
		CurrentContainer = Container;

	std::vector<RElement*> allElements = CurrentContainer->GetAllElements<RElement>();
	for (auto element : allElements)
	{
		std::string postfix;
		if (element->GetClass() == RContainer::StaticClass())
			postfix = "/";

		Dialogue->Write(element->GetName() + postfix + "  ");
	}
	Dialogue->WriteLine("");
	return true;
}

bool TElementExplorer::cmd_cc(const std::string& InContainerName)
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

bool TElementExplorer::cmd_attrlist(RElement* const & InElementName, std::string const & InAttributeName)
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
				Dialogue->WriteLine(attributeName + " \t(" + attribute->ObjectType().ToEasyString() + ")");
			}
			result = true;
		}
		else
		{
			ObjectMirror* attributeMirror = InElementName->GetAttribute(InAttributeName);
			if (attributeMirror)
			{
				// try to convert 
				auto converter = GlobalAtomConverterProvider()->GetConverter(attributeMirror->ObjectType());
				std::string value;
				if (converter)
				{
					value = converter->ObjectToString(attributeMirror->Object());
				}
				else
				{
					value = "<No Reflection.>";
				}

				// get arguments if functioninterface
				std::string argumentTypes;
				if (attributeMirror->ObjectType().Decay() == TypeID::FromType<RFunction*>())
				{
					RFunction* function = attributeMirror->Object().CastAndDereference<RFunction*>();
					auto v_argumentTypes = function->GetArgumentTypes();
					for (auto argumentType : v_argumentTypes)
					{
						argumentTypes += std::string("\n\t") + (argumentType.IsConst() ? "IN" : "OUT") + "\t" + argumentType.ToEasyString();
					}
				}

				// write it out
				Dialogue->WriteLine("Type: \n\t\t" + attributeMirror->ObjectType().ToEasyString());
				if (argumentTypes == "")
					Dialogue->WriteLine("Value: \t" + value);
				else
					Dialogue->WriteLine("Args: \t" + argumentTypes);
			}
			else
			{
				Dialogue->WriteLine("Could not find attributeMirror named '" + InAttributeName + "'.");
			}
		}
	}
	else
	{
		Dialogue->WriteLine("Could not find element.");
	}
	return result;
}

bool TElementExplorer::cmd_func(RFunction *& OutFunction, RElement * const & InElement, std::string const & InFuncName)
{
	auto p_Func = InElement->GetAttribute(InFuncName);
	if (p_Func)
	{
		OutFunction = p_Func->Object().CastAndDereference<RFunction*>();

		Dialogue->WriteLine("Found function: " + InFuncName);
		return true;
	}
	else
	{
		Dialogue->WriteLine("Could not find function: " + InFuncName);
		return false;
	}
}

std::string TElementExplorer::GetCurrentPath()
{
	RContainer* current = nullptr;
	RContainer* next = CurrentContainer;
	std::string result;

	do
	{
		current = next;
		next = next->GetContainer();
		if (next == current) { next = nullptr; }
		result = current->GetName() + "/" + result;
	} while (next);

	return result;
}
