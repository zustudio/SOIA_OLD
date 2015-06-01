
#pragma once

#include "Element_ID.h"

namespace Environment
{
	class MathContainer;
	class Constant;
	class LIBIMPEXP GenericMathFunction
	{
	public:
		GenericMathFunction(MathContainer* InRuntime, const Element_ID &InFunction);
		double get(double x);

	private:
		MathContainer* MathRuntime;
		Element_ID Function;
		Element_ID FunctionCall;
		Constant* FunctionArgument0;
	};
}