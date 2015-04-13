
#pragma once

#include "Operation.h"

namespace Environment
{
	class FunctionCache;
	class DLLIMPEXP OP_CalculateFunction : public Operation
	{
	public:
		OP_CalculateFunction(FunctionCache* InFuncCache, const std::vector<Value_ID> &InOperands);
		virtual double Calculate(const std::vector<Value*> &DefinedValues) override;

		FunctionCache* FuncCache;
	};
}