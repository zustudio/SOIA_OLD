
#pragma once

#include "TokenCollapseInterface.h"

namespace Environment
{
	enum class EParenthesisType : int
	{
		Start,
		End
	};
	class LIBIMPEXP TokenCollapseParenthesis : public TokenCollapseInterface
	{
	public:
		TokenCollapseParenthesis(EParenthesisType InType, int InID = 0);

		virtual bool Collapse(const Iterators<std::vector<Token*>>& InIters) override;

		EParenthesisType Type;
		int ID;
	};
}