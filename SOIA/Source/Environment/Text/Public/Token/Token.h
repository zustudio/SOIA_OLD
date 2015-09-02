
#pragma once

#include "TokenArityInterface.h"

#include <string>
#include <list>


namespace Environment
{
	class LIBIMPEXP Token
	{
	public:
		
		Token(const std::string& InText, TokenArityInterface const * InCollapser, int InRuleIdentifier);

		void Move(Token* InToken);
		void MoveToList(std::list<Token*> & InOutTargetList);
	private:
		void Internal_MoveToList(std::list<Token*> & InOutTargetList);

	public:
		void Disable();

		Token* GetParentToken();
		std::list<Token*>& GetSubTokens();
		std::vector<Token*> GetSubTokenVector();

		TokenArityInterface const * TokenCollapser;
		std::string Text;
		ContainerAwareIteratorSet<std::list<Token*>>* ContainerIteratorSet;
		int RuleIdentifier;
	private:
		Token* ParentToken;
		std::list<Token*> SubTokens;
	};
}