
#include "Definitions.h"

#include "TokenArity_Parenthesis.h"
using namespace Environment;

#include "Token.h"
#include "TokenRule.h"

TokenArity_Parenthesis::TokenArity_Parenthesis(EParenthesisType InType, int InID)
	:
	Type(InType),
	ID(InID)
{
}

bool TokenArity_Parenthesis::Collapse(Token* InToken)
{
	if (Type == EParenthesisType::End)
		return true;

	bool result = false;

	int openParenthesis = 1;
	ContainerAwareIteratorSet<std::list<Token*>> const & tokenIteratorSet = *InToken->ContainerIteratorSet;
	auto iter_currentToken = tokenIteratorSet.Current;
	iter_currentToken++;

	for (iter_currentToken; iter_currentToken != tokenIteratorSet.End; iter_currentToken++)
	{
		Token* currentToken = *iter_currentToken;
		TokenArity_Parenthesis const * collapseParenthesis = dynamic_cast<TokenArity_Parenthesis const *>(currentToken->TokenCollapser);
		if (collapseParenthesis && collapseParenthesis->ID == ID)
		{
			switch (collapseParenthesis->Type)
			{
			case EParenthesisType::Start:
				openParenthesis++;
				break;
			case EParenthesisType::End:
				openParenthesis--;
				break;
			default:
				break;
			}

			if (openParenthesis == 0)
			{
				break;
			}
		}
	}

	if (iter_currentToken != tokenIteratorSet.End)
	{
		auto iter_parenContentBegin = tokenIteratorSet.Current;
		auto iter_parenContentEnd = iter_currentToken;
		iter_parenContentBegin++;
		std::vector<Token*> tokensToMove;

		for (auto iter_subToken = iter_parenContentBegin; iter_subToken != iter_parenContentEnd; iter_subToken++)
		{
			tokensToMove.push_back(*iter_subToken);
		}
		for (Token* tokenToMove : tokensToMove)
		{
			tokenToMove->Move(*tokenIteratorSet.Current);
		}
		(*iter_parenContentEnd)->Disable();

		result = true;
	}

	return result;
}
