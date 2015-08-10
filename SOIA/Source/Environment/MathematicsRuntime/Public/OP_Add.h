
#pragma once

#include "Operation.h"

namespace Environment
{
	RCLASS(OP_Add,Operation);
	class LIBIMPEXP OP_Add : public OP_Add_Base
	{
	public:
		explicit OP_Add(const std::vector<ElementID> &InOperands = {});
		virtual double Calculate(const std::vector<Value*> &DefinedValues) override;
	};
}
