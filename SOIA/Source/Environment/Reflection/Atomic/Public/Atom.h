
#pragma once

#include <regex>
#include <vector>
#include <string>

#define ATOM_REFLECTION_FUNCTIONS(Class) \
	static std::string ToString(const Class& InObject); \
	static Class FromString(const std::string& InString);

namespace Environment
{
	class Atom
	{
	public:
		// definition for SFINAE
		typedef bool IsAtomType;

	protected:
		static std::vector<std::string> MatchPattern(const std::string& InInput, const std::string& InPattern);
	};
}