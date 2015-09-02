
#pragma once

#include "RElement.h"

#include <vector>

namespace Environment
{
	class DefinitionSet;
}

namespace Environment
{
	RABSTRACTCLASS(Value,RElement)
	class LIBIMPEXP Value: public Value_Base
	{
	public:
		virtual double Calculate(DefinitionSet* const & ForwardedDefinitions) = 0;
		virtual void PrepareCache() = 0;
	};
}