
#pragma once

#include "TokenCollapserInterface.h"

namespace Environment
{
	enum class EParenthesisType : int
	{
		Start,
		End
	};
	class LIBIMPEXP TokenCollapserParenthesis : public TokenCollapserInterface
	{
	public:
		TokenCollapserParenthesis(EParenthesisType InType, int InID = 0);

		virtual bool Collapse(Token* InToken) override;

		EParenthesisType Type;
		int ID;
	};
}