
#include "Definitions.h"

#include "TokenRule.h"
using namespace Environment;

#include "Token.h"

#include <regex>
#include <algorithm>

TokenRule::TokenRule(const std::string & InTextRegex, TokenCollapseInterface * InTokenCollapse)
	:
	TextRegex(InTextRegex),
	TokenCollapse(InTokenCollapse)
{}

void TokenRule::Clear()
{
	for (auto token : Tokens)
	{
		delete token;
	}
	Tokens.clear();
}

bool TokenRule::CreateToken(Iterators<std::string>& InTextIters, Token* InParent)
{
	bool result = false;

	std::regex regex(TextRegex);
	auto match = std::smatch();
	std::string text = std::string(InTextIters.Iterator, InTextIters.End);

	if (std::regex_search(text, match, regex))
	{
		if (match.position() == 0)
		{
			Token* token = new Token(match[1], InParent, this);
			Tokens.push_back(token);
			InParent->GetSubTokens().push_back(token);
			InTextIters.Iterator += (int)match.length();
			result = true;
		}
	}

	return result;
}

bool TokenRule::CollapseSubTokens(Token* InParent)
{
	bool result = true;

	std::vector<Token*>& globalTokens = InParent->GetSubTokens();

	for (auto myToken : Tokens)
	{
		auto globalIter = std::find(globalTokens.begin(), globalTokens.end(), myToken);
		if (globalIter == globalTokens.end()) 
			continue;	//error?
		Iterators<std::vector<Token*>> iterators = Iterators<std::vector<Token*>>(globalTokens, globalIter);
		result &= TokenCollapse->Collapse(iterators);

		//recursive call:
		CollapseSubTokens(myToken);
	}

	return result;
}


