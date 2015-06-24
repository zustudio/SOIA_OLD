
#pragma once

// include super class
#include "Value.h"

// include SOIA

// include std
#include <vector>

namespace Environment
{
	RABSTRACTCLASS(Operation,Value)
	class LIBIMPEXP Operation : public Operation_Base
	{
	public:
		explicit Operation(const std::vector<Element_ID> &InOperands = {});

		bool FindOperands(const std::vector<Value*> &InDefinedValues, Value* &OutOperand1, Value* &OutOperand2, Value* &OutOperand3);

		std::vector<Element_ID> Operands;
	};
}
