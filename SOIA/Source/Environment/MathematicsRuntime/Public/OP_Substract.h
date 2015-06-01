
#pragma once

#include "Operation.h"

namespace Environment
{
	RCLASS(OP_Substract,Operation)
	class LIBIMPEXP OP_Substract : public OP_Substract_Base
	{
	public:
		OP_Substract(const std::vector<Element_ID> &InOperands = {});
		virtual double Calculate(const std::vector<Value*> &DefinedValues) override;
	};
}
