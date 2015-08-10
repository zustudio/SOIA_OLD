
#pragma once

#include "RElement.h"

namespace Environment
{
	RCLASS(FunctionCacheItem,RElement)
	class FunctionCacheItem : public FunctionCacheItem_Base
	{
		RCLASS_BEGIN()
		FunctionCacheItem(const ElementID &InID = ElementID::DefaultObject(), const double &Inoperand0 = 0, const double &InResult = 0);
		ElementID CalledFunction;
		RPROPERTY(Operand0)
			double Operand0;
		RPROPERTY(Result)
			double Result;
		RCLASS_END()
	};
}