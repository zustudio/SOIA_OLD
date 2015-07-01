
#pragma once

#include "MathContainer.h"

#include <string>
#include <vector>
#include <deque>

namespace Environment
{
	enum class TokenType
	{
		VariableAssignment,
		FunctionAssignment,
		OpeningBracket,
		ClosingBracket,
		CollapsedBracket,
		MultiplyDivide,
		AddSubstract,
		Comparison,
		Number,
		Function,
		FunctionArgument0,
		Variable,
		Seperator,
		WhiteSpace

	};

	class LIBIMPEXP EquationToken
	{
	public:
		explicit EquationToken(const std::string& InString);
		void CollapseOperands(int& InMyPosition, std::deque<EquationToken*>& InAllTokens);

		Element_ID rec_RegisterToken(MathContainer* InRuntime);


		std::string String;
		TokenType Type;
		std::deque<EquationToken*> Operands;
	};
}