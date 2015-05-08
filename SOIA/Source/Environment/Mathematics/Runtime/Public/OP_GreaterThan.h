#pragma once

#include "Operation.h"

namespace Environment
{
	RCLASS(OP_GreaterThan,Operation)
	class DLLIMPEXP OP_GreaterThan : public OP_GreaterThan_Base
	{
	public:
		OP_GreaterThan(const std::vector<Element_ID> &InOperands = {});
		virtual double Calculate(const std::vector<Value*> &DefinedValues) override;
	};
}