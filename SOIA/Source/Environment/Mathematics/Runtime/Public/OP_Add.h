
#pragma once

#include "Operation.h"

namespace Environment
{
	class DLLIMPEXP OP_Add : public Operation
	{
	public:
		OP_Add(const std::vector<Value_ID> &InOperands);
		virtual double Calculate(const std::vector<Value*> &DefinedValues) override;
	};
}