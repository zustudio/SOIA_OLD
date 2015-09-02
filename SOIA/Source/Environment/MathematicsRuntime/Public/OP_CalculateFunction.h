
#pragma once

#include "Operation.h"

#include "MR_Function.h"

namespace Environment
{
	RCLASS(OP_CalculateFunction,Operation)
	class LIBIMPEXP OP_CalculateFunction : public OP_CalculateFunction_Base
	{
	public:
		OP_CalculateFunction(RPointer<Value> InFunctionDefinition = nullptr, std::vector<RPointer<Value>> const & InParameters = {});
		virtual double Calculate(DefinitionSet* const & ForwardedDefinitions) override;
		virtual void PrepareCache() override;

	private:
		RPointer<Value> FunctionDefinition;
	};
}