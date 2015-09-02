
#pragma once

#include "Operation.h"

namespace Environment
{
	RCLASS(OP_Substract,Operation)
	class LIBIMPEXP OP_Substract : public OP_Substract_Base
	{
	public:
		explicit OP_Substract(const std::vector<RPointer<Value>> &InOperands = {});
		virtual double Calculate(DefinitionSet* const & ForwardedDefinitions) override;
	};
}
