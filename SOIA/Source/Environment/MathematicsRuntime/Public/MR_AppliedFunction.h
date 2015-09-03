
#pragma once

#include "Operation.h"

#include "MR_Function.h"

namespace Environment
{
	RCLASS(MR_AppliedFunction,Operation)
	class LIBIMPEXP MR_AppliedFunction : public MR_AppliedFunction_Base
	{
	public:
		MR_AppliedFunction(RPointer<Value> InFunctionDefinition = nullptr, std::vector<RPointer<Value>> const & InParameters = {});
		void ApplyAsSpecialValue(double InResult);
		virtual double Calculate(DefinitionSet* const & ForwardedDefinitions) override;
		virtual void PrepareCache() override;

	private:
		RPointer<Value> FunctionDefinition;
	};
}