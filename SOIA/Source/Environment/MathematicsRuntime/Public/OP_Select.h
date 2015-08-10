
#pragma once

#include "Operation.h"

namespace Environment
{
	RCLASS(OP_Select,Operation)
	class LIBIMPEXP OP_Select : public OP_Select_Base
	{
	public:
		explicit OP_Select(const std::vector<ElementID> &InOperands = {});
		virtual double Calculate(const std::vector<Value*> &DefinedValues) override;
	};
}