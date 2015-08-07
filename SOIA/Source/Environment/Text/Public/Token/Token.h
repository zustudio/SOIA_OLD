
#pragma once

#include "TokenCollapserInterface.h"

#include <string>
#include <list>


namespace Environment
{
	class TokenRule;
	class LIBIMPEXP Token
	{
	public:
		
		Token(const std::string& InText, TokenCollapserInterface const * InCollapser);

		void Move(Token* InToken);
		void Move(std::list<Token*> & InOutTargetList);
		void Disable();

		std::list<Token*>& GetSubTokens();
		std::vector<Token*> GetSubTokenVector();

		TokenCollapserInterface const * TokenCollapser;
		std::string Text;
		ContainerAwareIteratorSet<std::list<Token*>>* ContainerIteratorSet;
	private:
		std::list<Token*> SubTokens;
	};
}