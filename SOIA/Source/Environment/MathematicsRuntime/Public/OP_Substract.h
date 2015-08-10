
#pragma once

#include "Operation.h"

namespace Environment
{
	RCLASS(OP_Substract,Operation)
	class LIBIMPEXP OP_Substract : public OP_Substract_Base
	{
	public:
		explicit OP_Substract(const std::vector<ElementID> &InOperands = {});
		virtual double Calculate(const std::vector<Value*> &DefinedValues) override;
	};
}
