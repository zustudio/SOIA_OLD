
#pragma once

#include "RElement.h"

#include <vector>


namespace Environment
{
	RABSTRACTCLASS(Value,RElement);
	class LIBIMPEXP Value: public Value_Base
	{
	public:
		virtual double Calculate(const std::vector<Value*> &DefinedValues) = 0;

	};
}