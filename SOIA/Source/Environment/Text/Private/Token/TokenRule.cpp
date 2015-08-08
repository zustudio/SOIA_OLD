
#include "Definitions.h"

#include "TokenRule.h"
using namespace Environment;

#include "Token.h"

#include <regex>
#include <algorithm>



TokenRule::TokenRule(std::regex const & InRegex, std::shared_ptr<TokenArityInterface> InTokenCollapser)
	:
	Regex(InRegex),
	TokenCollapser(InTokenCollapser),
	ParsedTokens()
{}

TokenRule::~TokenRule()
{}

void TokenRule::Clear()
{
	ParsedTokens.clear();
}

bool TokenRule::ParseNextToken(ContainerAwareIteratorSet<std::string> & InTextIteratorSet, std::list<Token*> & OutTokenList)
{
	bool result = false;

	std::string tokenText;
	int size = PeekNextToken(InTextIteratorSet, tokenText);
	if (size)
	{
		Token* token = new Token(tokenText, &*TokenCollapser);
		ParsedTokens.push_back(token);
		token->Move(OutTokenList);
		InTextIteratorSet.Current += size;
		
		result = true;
	}

	return result;
}

int TokenRule::PeekNextToken(ContainerAwareIteratorSet<std::string> const & InTextIteratorSet, std::string & OutTokenText) const
{
	int matchedCharCount = 0;
	OutTokenText = "";

	auto match = std::smatch();
	auto text = std::string(InTextIteratorSet.Current, InTextIteratorSet.End);

	if (std::regex_search(text, match, Regex))
	{
		if (match.position() == 0)
		{
			OutTokenText = match[1];
			matchedCharCount = match[0].str().size();
		}
	}
	return matchedCharCount;
}

bool TokenRule::CollapseTokens()
{
	for (Token* token : ParsedTokens)
	{
		TokenCollapser->Collapse(token);
	}

	return false;
}

