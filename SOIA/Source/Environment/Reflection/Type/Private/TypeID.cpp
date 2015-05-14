
#include "Environment/PreProcessor/Classes/PrivateDefinitions.h"

#include "Environment/Reflection/Type/Public/TypeID.h"
using namespace Environment;

#include <regex>

TypeID::TypeID(const std::string& InString)
{
	TypeString = InString;
}
bool TypeID::operator ==(const TypeID& InOther) const
{
	return TypeString == InOther.TypeString;
}
TypeID::operator std::string() const
{
	return TypeString;
}

bool TypeID::IsPointer() const
{
	return (TypeString[TypeString.size() - 1] == '*');
}

////////////////////////////////////////////////////////////////
// Operations
TypeID TypeID::Dereference() const
{
	if (IsPointer())
		return TypeID(std::string(TypeString.begin(), TypeString.end() - 2));
	else
		return TypeID(TypeString);
}
TypeID TypeID::RemoveSuffix_Base() const
{
	auto result = MatchPattern(TypeString, "class (\\w+)::(\\w+)_Base");
	if (result.size() == 3)
		return TypeID("class " + result[1] + "::" + result[2]);
	else
		return TypeID(TypeString);
}

////////////////////////////////////////////////////////////////
// Helpers
std::vector<std::string> TypeID::MatchPattern(const std::string& InInput, const std::string& InPattern)
{
	std::regex pattern(InPattern);
	auto result = std::smatch();
	bool success = std::regex_match(InInput, result, pattern);
	if (success)
	{
		return std::vector<std::string>(result.begin(), result.end());
	}
	else
	{
		return std::vector<std::string>();
	}
}