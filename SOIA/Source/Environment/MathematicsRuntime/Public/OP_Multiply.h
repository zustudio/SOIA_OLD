
#pragma once

#include "Operation.h"

namespace Environment
{
	RCLASS(OP_Multiply,Operation)
	class LIBIMPEXP OP_Multiply : public OP_Multiply_Base
	{
	public:
		explicit OP_Multiply(const std::vector<RPointer<Value>> &InOperands = {});
		virtual double Calculate(DefinitionSet* const & ForwardedDefinitions) override;
	};
}
