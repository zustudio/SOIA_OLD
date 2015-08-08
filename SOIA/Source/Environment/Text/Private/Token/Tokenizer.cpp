
#include "Definitions.h"

#include "Tokenizer.h"
using namespace Environment;


Tokenizer::Tokenizer(const std::vector<TokenRule>& InRules)
	:
	Rules(InRules),
	Tokens()
{}

bool Tokenizer::Tokenize(std::istream* InStream, TokenRule const& InStopTokenRule, std::list<Token*> & OutResult)
{
	std::string text;
	
	while (!InStream->eof())
	{
		/// read new character
		char c = InStream->get();
		text.push_back(c);

		std::string peekedTokenText;
		if (InStopTokenRule.PeekNextToken(ContainerAwareIteratorSet<std::string>(text, text.begin()), peekedTokenText))
		{
			break;
		}
	}

	return Tokenize(text, OutResult);
}

bool Tokenizer::Tokenize(std::string & InText, std::list<Token*> & OutResult)
{
	bool result = true;

	for (TokenRule& rule : Rules)
	{
		rule.Clear();
	}
	for (Token* token : Tokens)
	{
		delete token;
	}
	Tokens.clear();

	auto textIters = ContainerAwareIteratorSet<std::string>(InText, InText.begin());
	while (textIters.Current != textIters.End)
	{
		bool tokenFound = false;
		for (TokenRule& rule : Rules)
		{
			tokenFound = rule.ParseNextToken(textIters, Tokens);
			if (tokenFound)
				break;
		}

		if (!tokenFound)
			textIters.Current++;
	}
	for (TokenRule& rule : Rules)
	{
		rule.CollapseTokens();
	}
	OutResult = Tokens;

	return result;
}

