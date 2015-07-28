
#include "Definitions.h"

// include class
#include "RElement.h"
#include "RContainer.h"
using namespace Environment;

RElement::RElement()
	:
	Container(nullptr)
{
	GetElementReflectionProvider()->Register<RElement>();
	ReflectAttributes();
}
RElement::~RElement()
{
	for (ObjectMirror* attribute: AttributeMirrors)
	{
		delete attribute;
	}
}

void RElement::SetID(Element_ID InID)
{
	ID = InID;
}

Element_ID& RElement::GetID()
{
	return ID;
}

RContainer* RElement::GetContainer()
{
	return Container;
}

std::vector<std::string> RElement::GetAttributeNames()
{
	std::vector<std::string> result;
	for (auto mirror : AttributeMirrors)
	{
		result.push_back(mirror->GetName());
	}
	return result;
}

VoidPointer RElement::GetAttribute(const std::string& InName)
{
	for (auto mirror : AttributeMirrors)
	{
		if (mirror->GetName() == InName)
		{
			return mirror->Get();
		}
	}
	return VoidPointer::Nullpointer();
}

RClass* RElement::GetClass()
{
	return GetElementReflectionProvider()->GetClass(TypeID::FromType<RElement>());
}

RClass* RElement::StaticClass()
{
	return GetElementReflectionProvider()->GetClass(TypeID::FromType<RElement>());
}

//RClass* RElement::GetClassByType(const std::string& InType)
//{
//	return GetElementReflectionProvider()->GetClass(TypeID(InType));
//}

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
