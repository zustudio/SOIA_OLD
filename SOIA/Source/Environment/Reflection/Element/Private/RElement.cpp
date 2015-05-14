
#include "Environment/PreProcessor/Classes/PrivateDefinitions.h"

// include class
#include "Environment/Reflection/Element/Public/RElement.h"
using namespace Environment;

RElement::RElement()
{
	Reflect(ID);
}

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

RClass* RElement::GetClassByType(const std::string& InType)
{
	return GetElementReflectionProvider()->GetClass(TypeID(InType));
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

bool RElement::LoadReflection(const ElementReflection& InReflection, bool bIsPartial)
{
	int i;
	for (i = 0; i < InReflection.Attributes.size(); i++)
	{
		auto attribute = InReflection.Attributes[i];

		// check if attribute is a pointer
		//@ToDo: extract check into VoidPointer
		//@ToDo: maybe add checking for which attributes must be loaded at all
		//std::string id = attribute.GetTypeID();
		//if (id[id.length() - 1] == '*')
		//{
		//	// check if attribute is already loaded
		//	AttributeMirrors[i]->Get()
		//}

		bool success = AttributeMirrors[i]->SetIfTypesMatch(attribute);
		if (!success && !bIsPartial)
		{
			break;
		}
	}

	if (i == InReflection.Attributes.size())
		return true;
	else
		return false;
}
