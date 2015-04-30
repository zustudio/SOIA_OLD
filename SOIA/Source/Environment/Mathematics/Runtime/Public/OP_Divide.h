
#pragma once

#include "Operation.h"

namespace Environment
{
	class DLLIMPEXP OP_Divide : public Operation
	{
	public:
		OP_Divide(const std::vector<Element_ID> &InOperands);
		virtual double Calculate(const std::vector<Value*> &DefinedValues) override;
	};
}