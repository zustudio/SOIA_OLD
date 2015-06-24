
#pragma once

#include "MathContainer.h"
#include "EquationToken.h"

#include <string>
#include <vector>
#include <deque>

namespace Environment
{
	class LIBIMPEXP EquationTokens
	{
	public:
		explicit EquationTokens(const std::vector<std::string> &InFormalParts);

		EquationToken* GenerateOperandDependency();
		EquationToken* MultDivAddSubstDependency(std::deque<EquationToken*>& TokenList);
		EquationToken* VarAssignmentDependency(std::deque<EquationToken*>& TokenList);

		std::deque<EquationToken*> UnsortedTokens;
	};
}