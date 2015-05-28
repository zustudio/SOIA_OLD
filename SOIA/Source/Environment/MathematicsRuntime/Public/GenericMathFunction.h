
#pragma once

#include "Environment/Reflection/Element/Public/Element_ID.h"

namespace Environment
{
	class MathContainer;
	class Constant;
	class DLLIMPEXP GenericMathFunction
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