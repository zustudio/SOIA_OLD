
#pragma once

#include "Value.h"

#include <vector>

namespace Environment
{
	class DLLIMPEXP Constant : public Value
	{
	public:
		Constant(double InConstant);

		virtual double Calculate(const std::vector<Value*> &InDefinedValues) override;

		double myValue;
	};
}