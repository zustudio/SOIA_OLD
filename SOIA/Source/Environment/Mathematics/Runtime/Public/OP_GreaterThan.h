#pragma once

#include "Operation.h"

namespace Environment
{
	class DLLIMPEXP OP_GreaterThan : public Operation
	{
	public:
		OP_GreaterThan(const std::vector<Element_ID> &InOperands);
		virtual double Calculate(const std::vector<Value*> &DefinedValues) override;
	};
}