
#pragma once

#include "Operation.h"

namespace Environment
{
	RCLASS(OP_Multiply,Operation);
	class DLLIMPEXP OP_Multiply : public OP_Multiply_Base
	{
	public:
		OP_Multiply(const std::vector<Element_ID> &InOperands = {});
		virtual double Calculate(const std::vector<Value*> &DefinedValues) override;
	};
}
