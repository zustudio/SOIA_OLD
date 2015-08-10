
#pragma once

#include "Operation.h"

namespace Environment
{
	RCLASS(OP_Multiply,Operation);
	class LIBIMPEXP OP_Multiply : public OP_Multiply_Base
	{
	public:
		explicit OP_Multiply(const std::vector<ElementID> &InOperands = {});
		virtual double Calculate(const std::vector<Value*> &DefinedValues) override;
	};
}
