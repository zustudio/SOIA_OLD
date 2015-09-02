
#pragma once

#include "Operation.h"

namespace Environment
{
	RCLASS(OP_Select,Operation)
	class LIBIMPEXP OP_Select : public OP_Select_Base
	{
	public:
		explicit OP_Select(const std::vector<RPointer<Value>> &InOperands = {});
		virtual double Calculate(DefinitionSet* const & ForwardedDefinitions) override;
	};
}