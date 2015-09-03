
#include "Definitions.h"

#include "FunctionCache.h"
using namespace Environment;

#include <cmath>
#include <limits>

FunctionCache::FunctionCache()
	: BaseType()
{
}

void FunctionCache::CacheFunctionCall(std::vector<double> InOperands, double InResult)
{
	CachedItems.push_back(FunctionCacheItem(InOperands, InResult));
}

void FunctionCache::Clear()
{
	CachedItems.clear();
}

bool FunctionCache::GetCachedFunctionCall(std::vector<double> InOperands, double &OutResult)
{
	auto foundCachedItem = std::find(CachedItems.begin(), CachedItems.end(), InOperands);
	if (foundCachedItem == CachedItems.end())
	{
		OutResult = 0;
		return false;
	}
	else
	{
		OutResult = foundCachedItem->Result;
		return true;
	}
}


