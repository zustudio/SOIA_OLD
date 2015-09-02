
#pragma once

#include "Operation.h"

namespace Environment
{
	RCLASS(OP_If,Operation)
	class LIBIMPEXP OP_If : public OP_If_Base
	{
	public:
		explicit OP_If(const std::vector<RPointer<Value>> &InOperands = {});
		virtual double Calculate(DefinitionSet* const & ForwardedDefinitions) override;
	};
}