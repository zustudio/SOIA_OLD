
#pragma once

// include SOIA
#include "Token.h"
#include "TokenRule.h"

// include std
#include <list>

// class
namespace Environment
{
	class LIBIMPEXP Tokenizer
	{
		////////////////////////////////////////////////////////////////
		// Functions
	public:
		//----- init -----
		Tokenizer(const std::vector<TokenRule>& InRules);

		//----- public tokenizing -----
		bool Tokenize(std::istream* InStream, TokenRule const& InStopTokenRule, std::list<Token*> & OutResult);
		bool Tokenize(std::string& InText, std::list<Token*>& OutResult);

		////////////////////////////////////////////////////////////////
		// Variables
	private:
		std::vector<TokenRule> Rules;
		std::list<Token*> Tokens;
	};
}