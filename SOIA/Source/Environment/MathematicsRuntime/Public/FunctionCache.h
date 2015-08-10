
#pragma once

#include "RContainer.h"

#include "FunctionCacheItem.h"
#include <vector>

namespace Environment
{
	RCLASS(FunctionCache,RContainer)
	class LIBIMPEXP FunctionCache : public FunctionCache_Base
	{
	public:
		FunctionCache();
		bool GetCachedFunctionCall(const ElementID &InFunction, double InOperand0, double &OutResult);
		void CacheFunctionCall(const ElementID &InFunction, double InOperand0, double InResult);
		void Clear();

		bool DoublesEqual(const double& InA, const double& InB);
	};
}