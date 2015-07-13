
#include "Definitions.h"

#include "StringMatch.h"
using namespace Environment;

#include "Matrix2D.h"
#include "CharMatch.h"

#include <numeric>
#include <cmath>
#include <algorithm>

std::string StringMatch::GetBest(const std::string& InTest, const std::vector<std::string>& InList)
{
	std::vector<std::pair<std::string, int>> stringDistances;
	for (auto target : InList)
	{
		stringDistances.push_back(std::pair<std::string, int>(target, PartialMatch(target, InTest)));
	}
	std::pair<std::string, int> bestMatch = *stringDistances.begin();
	for (auto pair : stringDistances)
	{
		if (pair.second > bestMatch.second)
		{
			bestMatch = pair;
		}
	}
	return bestMatch.first;
}

int StringMatch::PartialMatch(const std::string& InTarget, const std::string& InTest)
{
	Vector2D<int> Size = Vector2D<int>(InTarget.size(), InTest.size());
	Matrix2D<int> ConsMatches = Matrix2D<int>(Size.X, Size.Y);

	for (int x = 0; x < Size.X; x++)
	{
		for (int y = 0; y < Size.Y; y++)
		{
			bool charMatch = CharMatch::IsEqual(InTarget[x], InTest[y], CharMatchOptions::IgnoreCase);
			int* p_lastCharVal = ConsMatches.get(x - 1, y - 1);
			int lastCharVal = p_lastCharVal ? *p_lastCharVal : 0;
			int newVal = charMatch ? lastCharVal + 1 : 0;
			ConsMatches.set(x, y, newVal);
		}
	}

	auto raw = ConsMatches.GetRawData();
	return *std::max_element(raw.begin(), raw.end());
}

int StringMatch::LevenshteinDistance(const std::string & s1, const std::string & s2)
{
	// To change the type this function manipulates and returns, change
	// the return type and the types of the two variables below.
	int s1len = s1.size();
	int s2len = s2.size();

	auto column_start = (decltype(s1len))1;

	auto column = new decltype(s1len)[s1len + 1];
	std::iota(column + column_start, column + s1len + 1, column_start);

	for (auto x = column_start; x <= s2len; x++) {
		column[0] = x;
		auto last_diagonal = x - column_start;
		for (auto y = column_start; y <= s1len; y++) {
			auto old_diagonal = column[y];
			auto possibilities = {
				column[y] + 1,
				column[y - 1] + 1,
				last_diagonal + (s1[y - 1] == s2[x - 1] ? 0 : 1)
			};
			column[y] = std::min(possibilities);
			last_diagonal = old_diagonal;
		}
	}
	auto result = column[s1len];
	delete[] column;
	return result;
}

int StringMatch::LevDistInternal(const std::string & InA, int SizeA, const std::string & InB, int SizeB)
{
	///* base case: empty strings */
	//if (SizeA == 0) return SizeB;
	//if (SizeB == 0) return SizeA;

	///* test if last characters of the strings match */
	//int cost;
	//if (InA[SizeA - 1] == InB[SizeB - 1])
	//	cost = 0;
	//else
	//	cost = 1;

	///* return minimum of delete char from s, delete char from t, and delete char from both */
	//return Environment::CompileTime::Minimum(LevDistInternal(InA, SizeA - 1, InB, SizeB) + 1,
	//	LevDistInternal(InA, SizeA, InB, SizeB - 1) + 1,
	//	LevDistInternal(InA, SizeA - 1, InB, SizeB - 1) + cost);
	return 0;
}
