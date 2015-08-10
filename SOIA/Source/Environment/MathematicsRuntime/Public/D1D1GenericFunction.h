
#pragma once

#include "D1D1FunctionInterface.h"

#include "ElementID.h"

namespace Environment
{
	class MathContainer;
	class Constant;
	class LIBIMPEXP D1D1GenericFunction : public D1D1FunctionInterface
	{
	public:
		D1D1GenericFunction(MathContainer* InRuntime, const ElementID &InFunction);
		virtual double Calculate(double x) override;
		ElementID GetFunctionID();

	private:
		MathContainer* MathRuntime;
		ElementID Function;
		ElementID FunctionCall;
		Constant* FunctionArgument0;
	};
}