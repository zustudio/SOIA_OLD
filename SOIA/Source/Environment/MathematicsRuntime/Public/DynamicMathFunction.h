
#pragma once

#include "Function.h"

#include "Value.h"

namespace Environment
{
	class MathContainer;
	class Value;
}

namespace Environment
{
	class LIBIMPEXP DynamicMathFunction : public Function<double, std::vector<double> const &>
	{
	public:
		DynamicMathFunction(MathContainer* InContainer, Value* InMathObject);
		virtual double Execute(std::vector<double> const &) override;
		std::string GetName();
		Value * GetValue();

	private:
		MathContainer* Container;
		Value* MathObject;
	};
}