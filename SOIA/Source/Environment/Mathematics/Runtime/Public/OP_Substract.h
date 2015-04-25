
#pragma once

#include "Operation.h"

namespace Environment
{
	class DLLIMPEXP OP_Substract : public Operation
	{
	public:
		OP_Substract(const std::vector<Element_ID> &InOperands);
		virtual double Calculate(const std::vector<Value*> &DefinedValues) override;
	};
}