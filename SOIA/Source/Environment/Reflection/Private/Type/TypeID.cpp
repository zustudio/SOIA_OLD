
#include "Definitions.h"

#include "TypeID.h"
using namespace Environment;

#include <regex>

TypeID::TypeID(const char* InString)
	:
	TypeString(InString)
{}
TypeID::TypeID(const std::string& InString)
	:
	TypeString(InString)
{}
bool TypeID::operator ==(const TypeID& InOther) const
{
	return TypeString == InOther.TypeString;
}
TypeID::operator std::string() const
{
	return TypeString;
}
std::string TypeID::ToString() const
{
	return *this;
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
		return TypeID(std::string(TypeString.begin(), TypeString.end() - 1));
	else
		return TypeID(TypeString);
}
TypeID TypeID::RemoveSuffix_Base() const
{
	auto result = MatchPattern(TypeString, "(\\w+)::(\\w+)_Base");
	if (result.size() == 3)
		return TypeID(result[1] + "::" + result[2]);
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

std::string TypeID::ParseName(const std::string& InName)
{
	std::string r1 = std::regex_replace(InName, std::regex(" \\*"), "*");
	std::string r2 = std::regex_replace(r1, std::regex("class "), "");
	std::string r3 = std::regex_replace(r2, std::regex(", "), ",");
	return r2;
}

#ifdef __GNUG__ // GCC
#include <cxxabi.h>
#include <cstdlib>
std::string TypeID::ParseGCCName( const char* mangled_name )
{
    int status ;
    char* temp = __cxxabiv1::__cxa_demangle( mangled_name, nullptr, nullptr, &status ) ;
    if(temp)
    {
        std::string result(temp) ;
        std::free(temp);
        return result ;
    }
    else return mangled_name ;
}

#else // not GCC

inline std::string TypeID::ParseGCCName( const char* mangled_name ) { return mangled_name ; }

#endif // __GNUG__
