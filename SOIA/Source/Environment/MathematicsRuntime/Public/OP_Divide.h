
#pragma once

#include "Operation.h"

namespace Environment
{
	RCLASS(OP_Divide,Operation)
	class LIBIMPEXP OP_Divide : public OP_Divide_Base
	{
	public:
		explicit OP_Divide(const std::vector<ElementID> &InOperands = {});
		virtual double Calculate(const std::vector<Value*> &DefinedValues) override;
	};
}