
#pragma once

#include <regex>
#include <vector>
#include <string>

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