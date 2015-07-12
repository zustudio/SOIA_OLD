
#include "Definitions.h"

#include "TokenCollapseParenthesis.h"
using namespace Environment;

#include "Token.h"
#include "TokenRule.h"

TokenCollapseParenthesis::TokenCollapseParenthesis(EParenthesisType InType, int InID)
	:
	Type(InType),
	ID(InID)
{
}

bool TokenCollapseParenthesis::Collapse(const Iterators<std::vector<Token*>>& InIters)
{
	if (Type == EParenthesisType::End)
		return true;

	bool result = false;

	int openParenthesis = 1;
	auto tokenIter = (InIters.Iterator + 1);
	for (tokenIter; tokenIter != InIters.End; tokenIter++)
	{
		Token* currentToken = *tokenIter;
		TokenCollapseParenthesis* collapseParenthesis = dynamic_cast<TokenCollapseParenthesis*>(currentToken->Rule->TokenCollapse);
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

	if (tokenIter != InIters.End)
	{
		Token* target = *InIters.Iterator;
		std::vector<Token*> subTokens;
		auto subTokenIter = (InIters.Iterator + 1);
		for (subTokenIter; subTokenIter != tokenIter; subTokenIter++)
		{
			subTokens.push_back(*subTokenIter);
			
		}
		(*tokenIter)->Disable();
		for (auto subToken : subTokens)
		{
			subToken->Move(target);
		}
		result = true;
	}

	return result;
}
