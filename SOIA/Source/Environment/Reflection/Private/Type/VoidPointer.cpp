
#include "Definitions.h"

#include "VoidPointer.h"
using namespace Environment;

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
