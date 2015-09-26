
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
	if (InOperands.size())
	{
		CachedItems.push_back(FunctionCacheItem(InOperands, InResult));
	}
}

void FunctionCache::Clear()
{
	CachedItems.clear();
}

bool FunctionCache::GetCachedFunctionCall(std::vector<double> InOperands, double &OutResult)
{
	auto foundCachedItem = std::find(CachedItems.rbegin(), CachedItems.rend(), InOperands);
	if (foundCachedItem == CachedItems.rend())
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


