
#pragma once

#include "Token.h"
#include "TokenRule.h"
#include "TokenCollapseNone.h"
#include "TokenCollapseParenthesis.h"

namespace Environment
{
	class LIBIMPEXP Tokenizer
	{
	public:
		Tokenizer(const std::vector<TokenRule>& InRules);

		bool Tokenize(std::string& InText);

		Token& GetResult();

	private:
		Token GlobalToken;
		std::vector<TokenRule> Rules;
	};
}