
#pragma once

#include "Value_ID.h"

namespace Environment
{
	class FunctionCacheItem
	{
	public:
		FunctionCacheItem(const Value_ID &InID, const double &Inoperand0, const double &InResult);
		Value_ID CalledFunction;
		double Operand0;
		double Result;
	};
}