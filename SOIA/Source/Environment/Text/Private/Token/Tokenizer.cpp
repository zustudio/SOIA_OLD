
#include "Definitions.h"

#include "Tokenizer.h"
using namespace Environment;

Tokenizer::Tokenizer(const std::vector<TokenRule>& InRules)
	:
	GlobalToken("GlobalToken", nullptr, nullptr),
	Rules(InRules)
{}

bool Tokenizer::Tokenize(std::string & InText)
{
	bool result = false;

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
	for (auto rule : Rules)
	{
		rule.CollapseSubTokens(&GlobalToken);
	}

	return result;
}

Token& Tokenizer::GetResult()
{
	return GlobalToken;
}
