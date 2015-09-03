
#pragma once

#include "RElement.h"

#include "FunctionCacheItem.h"
#include <vector>

namespace Environment
{
	RCLASS(FunctionCache,RElement)
	class LIBIMPEXP FunctionCache : public FunctionCache_Base
	{
	public:
		FunctionCache();
		bool GetCachedFunctionCall(std::vector<double> InOperands, double &OutResult);
		void CacheFunctionCall(std::vector<double> InOperands, double InResult);
		void Clear();

	private:
		std::vector<FunctionCacheItem> CachedItems;
	};
}