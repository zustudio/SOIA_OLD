
#pragma once

#include "Environment/Mathematics/Runtime/Public/MathContainer.h"

namespace Environment
{
	class DLLIMPEXP FunctionObject
	{
	public:
		FunctionObject(MathContainer* InRuntime, const Value_ID &InFunction);
		double get(double x);

	private:
		MathContainer* MathRuntime;
		Value_ID Function;
		Value_ID FunctionCall;
	};
}