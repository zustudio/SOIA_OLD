
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
ElementID& RContainer::Register(RElement* InObject, const std::string &InName)
{
	ElementID freeID = NextFreeID();

	std::string name = InName;
	NextFreeName(name);

	InObject->Registered(ElementRegistrationInfo(this, freeID, name));

	Objects.push_back(InObject);

	return InObject->GetID();
}
ElementID& RContainer::ReRegister(const ElementID& InID, RElement* InObject)
{
	// if new object is already registered, unregister it
	Unregister(InObject);

	RElement** ObjectToReplace = GetElementPointer(InID);
	if (ObjectToReplace)
	{
		InObject->Registered(ElementRegistrationInfo(this, InID, InObject->Name));

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
RElement** RContainer::GetElementPointer(const ElementID &InID)
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
		if (Objects[i]->Name == InName)
		{
			result = &Objects[i];
			break;
		}
	}
	return result;
}

////////////////////////////////////////////////////////////////
// Private ID Management
ElementID RContainer::NextFreeID()
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
			lastUniqueIdentifier = lastObject->GetID();
		} while (!AllowedIDs.IsInRange(lastUniqueIdentifier));
	}

	assert(lastUniqueIdentifier < AllowedIDs.Upper - 1);

	ElementID freeID = ElementID(lastUniqueIdentifier + 1);

	return freeID;
}
void RContainer::NextFreeName(std::string &InOutName)
{
	if (InOutName != "")
	{
		for (RElement* element : Objects)
		{
			if (element->Name == InOutName)
			{
				InOutName += "+";
				NextFreeName(InOutName);
				break;
			}
		}
	}
	return;
}
