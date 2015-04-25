
#pragma once

#include "Element_ID.h"

namespace Environment
{
	class FunctionCacheItem
	{
	public:
		FunctionCacheItem(const Element_ID &InID, const double &Inoperand0, const double &InResult);
		Element_ID CalledFunction;
		double Operand0;
		double Result;
	};
}