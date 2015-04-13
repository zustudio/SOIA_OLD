
#pragma once

// include super class
#include "Value.h"

// include SOIA
#include "Value_ID.h"

// include std
#include <vector>

namespace Environment
{
	class DLLIMPEXP Operation : public Value
	{
	public:
		Operation(const std::vector<Value_ID> &InOperands);

		bool FindOperands(const std::vector<Value*> &InDefinedValues, Value* &OutOperand1, Value* &OutOperand2, Value* &OutOperand3);

		std::vector<Value_ID> Operands;
	};
}