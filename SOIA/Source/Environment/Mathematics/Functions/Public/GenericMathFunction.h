
#pragma once

#include "Environment/Mathematics/Runtime/Public/MathContainer.h"

namespace Environment
{
	class DLLIMPEXP GenericMathFunction
	{
	public:
		GenericMathFunction(MathContainer* InRuntime, const Element_ID &InFunction);
		double get(double x);

	private:
		MathContainer* MathRuntime;
		Element_ID Function;
		Element_ID FunctionCall;
	};
}