
#pragma once

#include "FunctionCacheItem.h"

#include <vector>

namespace Environment
{
	class DLLIMPEXP FunctionCache
	{
	public:
		FunctionCache();
		bool GetCachedFunctionCall(const Element_ID &InFunction, double InOperand0, double &OutResult);
		void CacheFunctionCall(const Element_ID &InFunction, double InOperand0, double InResult);
		void Clear();
	private:
		std::vector<FunctionCacheItem> CachedFunctions;
	};
}