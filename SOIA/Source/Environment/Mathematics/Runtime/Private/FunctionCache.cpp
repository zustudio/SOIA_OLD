
#include "Environment/PreProcessor/Classes/PrivateDefinitions.h"

#include "Environment/Mathematics/Runtime/Public/FunctionCache.h"
using namespace Environment;

#include <cmath>
#include <limits>

FunctionCache::FunctionCache()
{
	CachedFunctions = std::vector<FunctionCacheItem>();
}

void FunctionCache::CacheFunctionCall(const Element_ID &InFunction, double InOperand0, double InResult)
{
	CachedFunctions.push_back(FunctionCacheItem(InFunction, InOperand0, InResult));
}

bool FunctionCache::GetCachedFunctionCall(const Element_ID &InFunction, double InOperand0, double &OutResult)
{
	bool result = false;
	for (FunctionCacheItem functionCall : CachedFunctions)
	{
		if (InFunction == functionCall.CalledFunction)
		{
			if (DoublesEqual(InOperand0, functionCall.Operand0))
			{
				OutResult = functionCall.Result;
				result = true;
			}
		}
	}
	return result;
}

void FunctionCache::Clear()
{
	CachedFunctions.clear();
}

bool FunctionCache::DoublesEqual(const double& InA, const double& InB)
{
	return std::abs(double(InA - InB)) < std::numeric_limits<double>::epsilon();
}
