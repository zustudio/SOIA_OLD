
#pragma once

// include super class
#include "Value.h"

// include SOIA
#include "RPointer.h"

// include std
#include <vector>

namespace Environment
{
	RABSTRACTCLASS(Operation,Value)
	class LIBIMPEXP Operation : public Operation_Base
	{
	public:
		explicit Operation(const std::vector<RPointer<Value>> &InOperands = {});

		virtual void PrepareCache() override;

		std::vector<RPointer<Value>> Operands;
	};
}
