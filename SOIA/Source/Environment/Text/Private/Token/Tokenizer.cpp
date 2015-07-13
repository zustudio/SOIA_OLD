
#include "Definitions.h"

#include "Tokenizer.h"
using namespace Environment;

Tokenizer::Tokenizer(const std::vector<TokenRule>& InRules)
	:
	GlobalToken("GlobalToken", nullptr, nullptr),
	Rules(InRules)
{}

bool Tokenizer::Tokenize(std::string & InText, Token*& OutResult)
{
	bool result = false;

	for (TokenRule& rule : Rules)
	{
		rule.Clear();
	}
	GlobalToken.GetSubTokens().clear();

	auto textIters = Iterators<std::string>(InText, InText.begin());
	while (textIters.Iterator != textIters.End)
	{
		bool tokenMatched = false;
		for (TokenRule& rule : Rules)
		{
			tokenMatched = rule.CreateToken(textIters, &GlobalToken);
			if (tokenMatched)
				break;
		}

		if (!tokenMatched)
			textIters.Iterator++;
	}
	for (TokenRule& rule : Rules)
	{
		rule.CollapseSubTokens(&GlobalToken);
	}
	OutResult = &GlobalToken;

	return result;
}

