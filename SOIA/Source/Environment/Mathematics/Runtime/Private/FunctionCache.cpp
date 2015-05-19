
#include "Environment/PreProcessor/Classes/PrivateDefinitions.h"

#include "Environment/Mathematics/Runtime/Public/FunctionCache.h"
using namespace Environment;

#include <cmath>
#include <limits>

FunctionCache::FunctionCache() : BaseType(Range<int>(0,100000))
{
}

void FunctionCache::CacheFunctionCall(const Element_ID &InFunction, double InOperand0, double InResult)
{
	Register(new FunctionCacheItem(InFunction, InOperand0, InResult));
}

bool FunctionCache::GetCachedFunctionCall(const Element_ID &InFunction, double InOperand0, double &OutResult)
{
	bool result = false;
	for (RElement* element : Objects)
	{
		FunctionCacheItem* functionCall = (FunctionCacheItem*)element;
		if (InFunction == functionCall->CalledFunction)
		{
			if (DoublesEqual(InOperand0, functionCall->Operand0))
			{
				OutResult = functionCall->Result;
				result = true;
			}
		}
	}
	return result;
}

bool FunctionCache::DoublesEqual(const double& InA, const double& InB)
{
	return std::abs(double(InA - InB)) < std::numeric_limits<double>::epsilon();
}
