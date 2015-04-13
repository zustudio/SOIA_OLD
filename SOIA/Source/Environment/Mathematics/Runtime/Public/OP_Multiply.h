
#pragma once

#include "Operation.h"

namespace Environment
{
	class DLLIMPEXP OP_Multiply : public Operation
	{
	public:
		OP_Multiply(const std::vector<Value_ID> &InOperands);
		virtual double Calculate(const std::vector<Value*> &DefinedValues) override;
	};
}