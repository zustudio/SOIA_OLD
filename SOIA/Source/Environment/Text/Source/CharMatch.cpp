
#include "Definitions.h"

#include "CharMatch.h"
using namespace Environment;

bool CharMatch::IsEqual(char c1, char c2, CharMatchOptions InOption)
{
	if (InOption == CharMatchOptions::UseCase)
		return c1 == c2;
	else if (InOption == CharMatchOptions::IgnoreCase)
	{
		return ToLowerCase(c1) == ToLowerCase(c2);
	}
}

char Environment::CharMatch::ToLowerCase(char c)
{
	if (c >= 'A' && c <= 'Z')
		return c - 'A' + 'a';
	else
		return c;
}
