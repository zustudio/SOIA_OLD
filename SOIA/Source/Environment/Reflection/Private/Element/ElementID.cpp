
#include "Definitions.h"

// include class
#include "ElementID.h"
using namespace Environment;

// include std
#include <regex>

//////////////////////////////////////////////////////////////
// Init
ElementID::ElementID(int const & InIdentifier)
	:
	Identifier(InIdentifier)
{}
ElementID ElementID::DefaultObject()
{
	return ElementID(-1);
}
int const & ElementID::ToInt() const
{
	return Identifier;
}
std::string ElementID::ToString(const ElementID& InID)
{
	return std::to_string(InID.Identifier);
}
ElementID ElementID::FromString(const std::string& InString)
{
	/// Create default element id and get its properties
	ElementID newID = ElementID::DefaultObject();
	int identifier = newID.Identifier;

	/// if string is correctly formated overwrite default properties
	std::smatch match;
	std::regex_match(InString, match, std::regex("([0-9]+)"));
	if (match.size() == 2)
	{
		identifier = std::atoi(std::string(match[1]).c_str());
	}

	/// return updated properties
	return ElementID(identifier);
}

////////////////////////////////////////////////////////////////
// Operators
ElementID::operator int() const
{
	return Identifier;
}
bool ElementID::operator== (const ElementID &InOther) const
{
	bool result = false;

	if (Identifier == InOther.Identifier)
	{
		result = true;
	}

	return result;
}

