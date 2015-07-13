
#pragma once

#include "TokenCollapseInterface.h"

#include <string>
#include <vector>

namespace Environment
{
	class LIBIMPEXP TokenRule
	{
	public:

		TokenRule(const std::string& InTextRegex, TokenCollapseInterface* InTokenCollapse);

		void Clear();
		bool CreateToken(Iterators<std::string>& InTextIters, Token* Parent);
		bool CollapseSubTokens(Token* Parent);

		std::vector<Token*> Tokens;
		std::string TextRegex;
		TokenCollapseInterface* TokenCollapse;
	};
}