
#pragma once

#include "Operation.h"

namespace Environment
{
	RCLASS(OP_If,Operation)
	class LIBIMPEXP OP_If : public OP_If_Base
	{
	public:
		explicit OP_If(const std::vector<Element_ID> &InOperands = {});
		virtual double Calculate(const std::vector<Value*> &DefinedValues) override;
	};
}