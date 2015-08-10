
#include "Definitions.h"

#include "FunctionCacheItem.h"
using namespace Environment;

FunctionCacheItem::FunctionCacheItem(const ElementID &InID, const double &Inoperand0, const double &InResult) 
	: BaseType(),
	CalledFunction(InID),
	Operand0(Inoperand0),
	Result(InResult)
{
	ReflectAttributes();
}