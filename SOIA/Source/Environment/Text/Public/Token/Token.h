
#pragma once

#include "TokenArityInterface.h"

#include <string>
#include <list>


namespace Environment
{
	class TokenRule;
	class LIBIMPEXP Token
	{
	public:
		
		Token(const std::string& InText, TokenArityInterface const * InCollapser);

		void Move(Token* InToken);
		void Move(std::list<Token*> & InOutTargetList);
		void Disable();

		std::list<Token*>& GetSubTokens();
		std::vector<Token*> GetSubTokenVector();

		TokenArityInterface const * TokenCollapser;
		std::string Text;
		ContainerAwareIteratorSet<std::list<Token*>>* ContainerIteratorSet;
	private:
		std::list<Token*> SubTokens;
	};
}