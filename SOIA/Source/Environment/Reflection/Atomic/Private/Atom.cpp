
#include "Environment/PreProcessor/Classes/PrivateDefinitions.h"

#include "Environment/Reflection/Atomic/Public/Atom.h"
using namespace Environment;

std::vector<std::string> Atom::MatchPattern(const std::string& InInput, const std::string& InPattern)
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