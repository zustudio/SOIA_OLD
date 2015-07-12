
#pragma once

#include <string>
#include <vector>

namespace Environment
{
	class LIBIMPEXP StringMatch
	{
	public:
		static std::string GetBest(const std::string& Target, const std::vector<std::string>& InList);
		static int PartialMatch(const std::string & InTarget, const std::string & InTest);
		static int LevenshteinDistance(const std::string& InA, const std::string& InB);
		static int LevDistInternal(const std::string& InA, int SizeA, const std::string& InB, int SizeB);
	};
}