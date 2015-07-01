
#pragma once

#include "RElement.h"

namespace Environment
{
	RCLASS(FunctionCacheItem,RElement)
	class FunctionCacheItem : public FunctionCacheItem_Base
	{
	public:
		FunctionCacheItem(const Element_ID &InID = Element_ID(), const double &Inoperand0 = 0, const double &InResult = 0);
		Element_ID CalledFunction;
		double Operand0;
		double Result;
	};
}