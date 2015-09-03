
#include "Definitions.h"

#include "FunctionCacheItem.h"
using namespace Environment;

FunctionCacheItem::FunctionCacheItem(std::vector<double> InOperands, double InResult) 
	: BaseType(),
	Operands(InOperands),
	Result(InResult)
{
}

bool FunctionCacheItem::operator==(std::vector<double> const& InOperands)
{
	for (int i = 0; i < Operands.size(); ++i)
	{
		if (!DoublesEqual(Operands[i], InOperands[i]))
			return false;
	}
	return true;
}

bool FunctionCacheItem::DoublesEqual(const double& InA, const double& InB)
{
	return std::abs(double(InA - InB)) < std::numeric_limits<double>::epsilon();
}