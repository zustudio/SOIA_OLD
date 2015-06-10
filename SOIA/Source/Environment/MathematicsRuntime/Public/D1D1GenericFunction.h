
#pragma once

#include "D1D1FunctionInterface.h"

#include "Element_ID.h"

namespace Environment
{
	class MathContainer;
	class Constant;
	class LIBIMPEXP D1D1GenericFunction : public D1D1FunctionInterface
	{
	public:
		D1D1GenericFunction(MathContainer* InRuntime, const Element_ID &InFunction);
		virtual double Calculate(double x) override;

	private:
		MathContainer* MathRuntime;
		Element_ID Function;
		Element_ID FunctionCall;
		Constant* FunctionArgument0;
	};
}