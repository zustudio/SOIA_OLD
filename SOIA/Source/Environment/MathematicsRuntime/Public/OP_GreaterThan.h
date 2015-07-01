#pragma once

#include "Operation.h"

namespace Environment
{
	RCLASS(OP_GreaterThan,Operation)
	class LIBIMPEXP OP_GreaterThan : public OP_GreaterThan_Base
	{
	public:
		explicit OP_GreaterThan(const std::vector<Element_ID> &InOperands = {});
		virtual double Calculate(const std::vector<Value*> &DefinedValues) override;
	};
}