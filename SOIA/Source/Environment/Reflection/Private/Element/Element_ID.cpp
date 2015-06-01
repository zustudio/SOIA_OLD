
#include "Definitions.h"

// include class
#include "Element_ID.h"
using namespace Environment;

////////////////////////////////////////////////////////////////
// Init
Element_ID::Element_ID()
{
	UniqueIdentifier = 35505;
}
std::string Element_ID::ToString(const Element_ID& InID)
{
	return std::to_string(InID.UniqueIdentifier) + "," + InID.Name;
}
Element_ID Element_ID::FromString(const std::string& InString)
{
	Element_ID id;
	auto result = MatchPattern(InString, "([0-9]+),(\\w+)?");
	if (result.size() == 3)
	{
		id.Name = result[2];
		id.UniqueIdentifier = std::atoi(std::string(result[1]).c_str());
	}
	return id;
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

