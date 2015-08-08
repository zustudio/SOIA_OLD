
#pragma once

#include "TokenArityInterface.h"

namespace Environment
{
	enum class EParenthesisType : int
	{
		Start,
		End
	};
	class LIBIMPEXP TokenArity_Parenthesis : public TokenArityInterface
	{
	public:
		TokenArity_Parenthesis(EParenthesisType InType, int InID = 0);

		virtual bool Collapse(Token* InToken) override;

		EParenthesisType Type;
		int ID;
	};
}