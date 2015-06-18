
#include "Definitions.h"

#include "VoidPointer.h"
using namespace Environment;
#include "ReflectionProviders.h"

const TypeID& VoidPointer::GetTypeID() const
{
	return ID;
}

void VoidPointer::OverrideType(const TypeID& InNewTypeID)
{
	ID = InNewTypeID;
}

bool VoidPointer::IsNullPointer()
{
	bool result = false;
	if (!Object)
	{
		result = true;
	}
	else if (ID.IsPointer())
	{
		result = *((void**)Object) == nullptr;
	}
	return result;
}

bool VoidPointer::IsChildOf(const TypeID& InOther) const
{
	auto reflectionProv = GetElementReflectionProvider();
	RClass* thisClass = reflectionProv->GetClass(ID.Dereference());
	RClass* otherClass = reflectionProv->GetClass(InOther.Dereference());
	return (thisClass && otherClass
			&& thisClass->IsChildOf(otherClass));
}
