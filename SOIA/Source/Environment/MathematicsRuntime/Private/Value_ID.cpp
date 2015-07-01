
#include "Environment/PreProcessor/Classes/PrivateDefinitions.h"

#include "Environment/Mathematics/Runtime/Public/Value_ID.h"
using namespace Environment;

Value_ID::Value_ID()
{
	UniqueIdentifier = 0;
	bIsConstant = true;
}

bool Value_ID::operator == (const Value_ID &other) const
{
	bool result = false;

	if (this->UniqueIdentifier == other.UniqueIdentifier)
	{
		result = true;
	}

	return result;
}
