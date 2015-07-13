
#pragma once

#include <string>
#include <vector>


namespace Environment
{
	class TokenRule;
	class LIBIMPEXP Token
	{
	public:
		
		Token(const std::string& InText, Token* InParent, TokenRule* InRule);

		void Move(Token* Target);
		void Disable();

		std::vector<Token*>& GetSubTokens();

		TokenRule* Rule;

		std::string Text;
	private:
		Token* Parent;
		std::vector<Token*> SubTokens;
	};
}