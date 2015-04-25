
#include "Environment/PreProcessor/Classes/PrivateDefinitions.h"

#include "Environment/Mathematics/Runtime/Public/FunctionCacheItem.h"
using namespace Environment;

FunctionCacheItem::FunctionCacheItem(const Element_ID &InID, const double &Inoperand0, const double &InResult)
{
	CalledFunction = InID;
	Operand0 = Inoperand0;
	Result = InResult;
}