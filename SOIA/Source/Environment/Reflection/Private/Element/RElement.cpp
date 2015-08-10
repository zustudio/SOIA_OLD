
#include "Definitions.h"

// include class
#include "RElement.h"
#include "RContainer.h"
using namespace Environment;

RElement::RElement()
	:
	Container(nullptr),
	ID(ElementID::DefaultObject())
{
	GetElementReflectionProvider()->Register<RElement>();
	ReflectAttributes();
}
RElement::~RElement()
{}

void RElement::Registered(ElementRegistrationInfo const & InInfo)
{
	Container = InInfo.Container;
	ID = InInfo.ID;
	Name = InInfo.Name;
}

ElementID& RElement::GetID()
{
	return ID;
}

RContainer* RElement::GetContainer()
{
	return Container;
}

std::vector<std::string> RElement::GetAttributeNames()
{
	std::vector<MemberMirror*> & memberMirrors = GetMemberMirrors();

	std::vector<std::string> result;
	for (auto memberMirror : memberMirrors)
	{
		result.push_back(memberMirror->Name);
	}
	return result;
}

ObjectMirror* RElement::GetAttribute(const std::string& InName)
{
	std::vector<MemberMirror*> & memberMirrors = GetMemberMirrors();

	for (auto memberMirror : memberMirrors)
	{
		if (memberMirror->Name == InName)
		{
			return memberMirror->ToObjectMirror(GetVoidPointer());
		}
	}
	return nullptr;
}

std::vector<ObjectMirror*> const Environment::RElement::GetAttributes()
{
	std::vector<MemberMirror*> & memberMirrors = GetMemberMirrors();
	std::vector<ObjectMirror*> objectMirrors;

	for (auto memberMirror : memberMirrors)
	{
		objectMirrors.push_back(memberMirror->ToObjectMirror(GetVoidPointer()));
	}
	return objectMirrors;
}
