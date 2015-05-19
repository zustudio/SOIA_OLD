
#pragma once

#include "Environment/Reflection/Element/Public/RContainer.h"

#include "FunctionCacheItem.h"
#include <vector>

namespace Environment
{
	RCLASS(FunctionCache,RContainer)
	class DLLIMPEXP FunctionCache : public FunctionCache_Base
	{
	public:
		FunctionCache();
		bool GetCachedFunctionCall(const Element_ID &InFunction, double InOperand0, double &OutResult);
		void CacheFunctionCall(const Element_ID &InFunction, double InOperand0, double InResult);
		void Clear();

		bool DoublesEqual(const double& InA, const double& InB);
	};
}