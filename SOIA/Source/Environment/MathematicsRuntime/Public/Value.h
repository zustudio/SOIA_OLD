
#pragma once

#include "Environment/Reflection/Element/Public/RElement.h"

#include <vector>


namespace Environment
{
	RABSTRACTCLASS(Value,RElement);
	class DLLIMPEXP Value: public Value_Base
	{
	public:
		virtual double Calculate(const std::vector<Value*> &DefinedValues) = 0;

	};
}