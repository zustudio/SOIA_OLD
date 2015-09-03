
#pragma once

#include "RElement.h"

namespace Environment
{
	RCLASS(FunctionCacheItem,RElement)
	class FunctionCacheItem : public FunctionCacheItem_Base
	{
		RCLASS_BEGIN()
			FunctionCacheItem(std::vector<double> InOperands = {}, double InResult = 0);
	
		bool operator==(std::vector<double> const& InOperands);

		static bool DoublesEqual(const double& InA, const double& InB);

		RPROPERTY(Operands)
			std::vector<double> Operands;
		RPROPERTY(Result)
			double Result;

		RCLASS_END()
	};
}