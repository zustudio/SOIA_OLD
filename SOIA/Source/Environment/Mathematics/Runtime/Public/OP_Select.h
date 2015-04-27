
#pragma once

#include "Operation.h"

namespace Environment
{
	class DLLIMPEXP OP_Select : public Operation
	{
	public:
		OP_Select(const std::vector<Element_ID> &InOperands);
		virtual double Calculate(const std::vector<Value*> &DefinedValues) override;
	};
}