
#pragma once

namespace Environment
{
	enum class CharMatchOptions : int
	{
		UseCase = 0,
		IgnoreCase = 1
	};
	class CharMatch
	{
	public:
		static bool IsEqual(char c1, char c2, CharMatchOptions InOption = CharMatchOptions::UseCase);
	private:
		static char ToLowerCase(char c);
	};
}