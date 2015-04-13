
#pragma once

#include "Value_ID.h"

#include <vector>

namespace Environment
{
	class DLLIMPEXP Value
	{
	public:
		virtual void SetID(Value_ID InID);

		virtual double Calculate(const std::vector<Value*> &DefinedValues) = 0;

		Value_ID ID;
	};
}