
#include "Definitions.h"

#include "VoidPointer.h"
using namespace Environment;
#include "ReflectionProviders.h"
#include "RElement.h"

const TypeID& VoidPointer::GetTypeID() const
{
	return Type;
}

void VoidPointer::OverrideType(const TypeID& InNewTypeID)
{
	Type = InNewTypeID;
}

VoidPointer::operator bool() const
{
	return IsValid();
}

bool VoidPointer::IsValid() const
{
	return Target;
}

bool VoidPointer::IsNullPointer()
{
	bool result = false;
	if (IsValid() && Type.IsPointer())
	{
		result = *((void**)Target) == nullptr;
	}
	return result;
}

bool VoidPointer::IsChildOf(const TypeID& InOther) const
{
	RElement** pp_element = CastTo<RElement*>();
	if (pp_element)
	{
		auto reflectionProv = GetElementReflectionProvider();
		RClass* thisClass = (*pp_element)->GetClass();
		RClass* otherClass = reflectionProv->GetClass(InOther.Dereference());
		return (thisClass && otherClass
			&& thisClass->IsChildOf(otherClass));
	}
	return false;
}
