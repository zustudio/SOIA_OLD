
#include "Environment/PreProcessor/Classes/PrivateDefinitions.h"

// include class
#include "Environment/Reflection/Element/Public/Element_ID.h"
using namespace Environment;

////////////////////////////////////////////////////////////////
// Init
Element_ID::Element_ID()
{
	UniqueIdentifier = 35505;
}

////////////////////////////////////////////////////////////////
// Access
bool Element_ID::operator== (const Element_ID &InOther) const
{
	bool result = false;

	if (this->UniqueIdentifier == InOther.UniqueIdentifier)
	{
		result = true;
	}

	return result;
}
