
#pragma once

#include "Value.h"

#include <vector>


namespace Environment
{
	RCLASS(Constant,Value)
	class LIBIMPEXP Constant : public Constant_Base
	{
	public:

		explicit Constant(double InConstant = 0);

		virtual double Calculate(DefinitionSet* const & ForwardedDefinitions) override;
		virtual void PrepareCache() override {}

		double myValue;
	};
}