
#pragma once

#include "Operation.h"

namespace Environment
{
	class DLLIMPEXP OP_If : public Operation
	{
	public:
		OP_If(const std::vector<Element_ID> &InOperands);
		virtual double Calculate(const std::vector<Value*> &DefinedValues) override;
	};
}