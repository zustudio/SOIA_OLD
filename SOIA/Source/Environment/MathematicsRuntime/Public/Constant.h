
#pragma once

#include "Value.h"

#include <vector>


namespace Environment
{
	RCLASS(Constant,Value);
	class LIBIMPEXP Constant : public Constant_Base
	{
	public:

		Constant(double InConstant = 0);

		virtual double Calculate(const std::vector<Value*> &InDefinedValues) override;

		double myValue;

		Constant* Next;
	};
}