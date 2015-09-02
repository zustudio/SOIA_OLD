#pragma once

#include "Operation.h"

namespace Environment
{
	RCLASS(OP_GreaterThan,Operation)
	class LIBIMPEXP OP_GreaterThan : public OP_GreaterThan_Base
	{
	public:
		explicit OP_GreaterThan(const std::vector<RPointer<Value>> &InOperands = {});
		virtual double Calculate(DefinitionSet* const & ForwardedDefinitions) override;
	};
}