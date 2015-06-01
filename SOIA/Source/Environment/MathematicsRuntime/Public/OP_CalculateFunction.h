
#pragma once

#include "Operation.h"

namespace Environment
{
	class FunctionCache;
	RCLASS(OP_CalculateFunction,Operation)
	class LIBIMPEXP OP_CalculateFunction : public OP_CalculateFunction_Base
	{
	public:
		OP_CalculateFunction(FunctionCache* InFuncCache = nullptr, const std::vector<Element_ID> &InOperands = {});
		virtual double Calculate(const std::vector<Value*> &DefinedValues) override;

		FunctionCache* FuncCache;
	};
}