
#include "Definitions.h"

#include "RContainer.h"
using namespace Environment;

#include <algorithm>

////////////////////////////////////////////////////////////////
// Init
RContainer::RContainer(const Range<int>& InAllowedIDs, const std::vector<RElement*>& InElements)
	:
	AllowedIDs(InAllowedIDs),
	Objects(InElements)
{
	ReflectAttributes();
}

////////////////////////////////////////////////////////////////
// Public Object Access
Element_ID& RContainer::Register(RElement* InObject, const std::string &InName)
{
	Element_ID freeID = NextFreeID();

	std::string name = InName;
	NextFreeName(name);
	freeID.Name = name;

	InObject->SetID(freeID);
	InObject->Container = this;

	Objects.push_back(InObject);

	return InObject->GetID();
}
Element_ID& RContainer::ReRegister(const Element_ID& InID, RElement* InObject)
{
	// if new object is already registered, unregister it
	Unregister(InObject);

	RElement** ObjectToReplace = GetElementPointer(InID);
	if (ObjectToReplace)
	{
		InObject->SetID(InID);
		InObject->Container = this;

		*ObjectToReplace = InObject;

		return InObject->GetID();
	}
	else
	{
		return Register(InObject);
	}
}
void RContainer::Unregister(RElement* Object)
{
	auto foundObject = std::find(Objects.begin(), Objects.end(), Object);
	if (foundObject != Objects.end())
	{
		Objects.erase(foundObject);
	}
}
void RContainer::Clear()
{
	Objects.clear();
}
RElement** RContainer::GetElementPointer(const Element_ID &InID)
{
	std::vector<RContainer*> subContainers;
	RElement** result = nullptr;
	int n = Objects.size();

	for (int i = 0; i < n; i++)
	{
		if (Objects[i]->GetID() == InID)
		{
			result = &Objects[i];
			break;
		}
		else if (Objects[i]->GetClass()->IsChildOf(RContainer::StaticClass()))
		{
			subContainers.push_back(dynamic_cast<RContainer*>(Objects[i]));
		}
	}

	if (!result)
	{
		for (auto container : subContainers)
		{
			result = container->GetElementPointer(InID);
			if (result)
				break;
		}
	}

	return result;
}
RElement** RContainer::GetElementPointer(const std::string &InName)
{
	RElement** result = nullptr;
	int n = Objects.size();

	for (int i = 0; i < n; i++)
	{
		if (Objects[i]->GetID().Name == InName)
		{
			result = &Objects[i];
			break;
		}
	}
	return result;
}

////////////////////////////////////////////////////////////////
// Private ID Management
Element_ID RContainer::NextFreeID()
{
	int lastUniqueIdentifier;
	if (Objects.size() == 0)
	{
		lastUniqueIdentifier = AllowedIDs.Lower - 1;
	}
	else
	{
		auto i_Object = Objects.end();
		do
		{
			i_Object--;
			RElement* lastObject = *i_Object;
			lastUniqueIdentifier = lastObject->GetID().UniqueIdentifier;
		} while (!AllowedIDs.IsInRange(lastUniqueIdentifier));
	}

	assert(lastUniqueIdentifier < AllowedIDs.Upper - 1);

	Element_ID freeID = Element_ID();
	freeID.UniqueIdentifier = lastUniqueIdentifier + 1;

	return freeID;
}
void RContainer::NextFreeName(std::string &InOutName)
{
	if (InOutName != "")
	{
		for (RElement* element : Objects)
		{
			if (element->GetID().Name == InOutName)
			{
				InOutName += "+";
				NextFreeName(InOutName);
				break;
			}
		}
	}
	return;
}
