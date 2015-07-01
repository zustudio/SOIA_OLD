
#include "Definitions.h"

#include "VoidPointer.h"
using namespace Environment;
#include "ReflectionProviders.h"

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
	auto reflectionProv = GetElementReflectionProvider();
	RClass* thisClass = reflectionProv->GetClass(Type.Dereference());
	RClass* otherClass = reflectionProv->GetClass(InOther.Dereference());
	return (thisClass && otherClass
			&& thisClass->IsChildOf(otherClass));
}
