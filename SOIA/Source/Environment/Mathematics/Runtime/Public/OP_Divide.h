
#pragma once

#include "Operation.h"

namespace Environment
{
	RCLASS(OP_Divide,Operation)
	class DLLIMPEXP OP_Divide : public OP_Divide_Base
	{
	public:
		OP_Divide(const std::vector<Element_ID> &InOperands = {});
		virtual double Calculate(const std::vector<Value*> &DefinedValues) override;
	};
}