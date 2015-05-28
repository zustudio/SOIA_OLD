
#pragma once

#include "Operation.h"

namespace Environment
{
	RCLASS(OP_Select,Operation)
	class DLLIMPEXP OP_Select : public OP_Select_Base
	{
	public:
		OP_Select(const std::vector<Element_ID> &InOperands = {});
		virtual double Calculate(const std::vector<Value*> &DefinedValues) override;
	};
}