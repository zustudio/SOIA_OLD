
#include "Definitions.h"

#include "TokenCollapserParenthesis.h"
using namespace Environment;

#include "Token.h"
#include "TokenRule.h"

TokenCollapserParenthesis::TokenCollapserParenthesis(EParenthesisType InType, int InID)
	:
	Type(InType),
	ID(InID)
{
}

bool TokenCollapserParenthesis::Collapse(Token* InToken)
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
		TokenCollapserParenthesis const * collapseParenthesis = dynamic_cast<TokenCollapserParenthesis const *>(currentToken->TokenCollapser);
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

		for (auto iter_subToken = iter_parenContentBegin; iter_subToken != iter_parenContentEnd; iter_subToken++)
		{
			(*iter_subToken)->Move(*tokenIteratorSet.Current);
		}
		result = true;
	}

	return result;
}
