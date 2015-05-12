
#include "Environment/PreProcessor/Classes/PrivateDefinitions.h"

// include class
#include "Environment/Reflection/Element/Public/RElement.h"
using namespace Environment;


void RElement::SetID(Element_ID InID)
{
	ID = InID;
}

Element_ID& RElement::GetID()
{
	return ID;
}

RClass* RElement::GetClass()
{
	return GetClassByType(typeid(RElement).name());
}

RClass* RElement::GetClassByType(const std::string& InTypeID)
{
	return GetElementReflectionProvider()->GetClass(InTypeID);
}

ElementReflection RElement::CreateReflection()
{
	std::vector<VoidPointer> attributes;
	for (auto mirror : AttributeMirrors)
	{
		attributes.push_back(mirror->Get());
	}
	return ElementReflection(attributes);
}

bool RElement::LoadReflection(const ElementReflection& InReflection)
{
	int i;
	for (i = 0; i < InReflection.Attributes.size(); i++)
	{
		auto attribute = InReflection.Attributes[i];
		bool success = AttributeMirrors[i]->SetIfTypesMatch(attribute);
		if (!success)
		{
			break;
		}
	}

	if (i == InReflection.Attributes.size())
		return true;
	else
		return false;
}
