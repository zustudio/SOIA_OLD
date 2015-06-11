
#pragma once

#include "Definitions.h"

#include "VoidPointer.h"

#include <vector>

namespace Environment
{
	class LIBIMPEXP FunctionInterface
	{
	public:
		virtual bool Execute(const std::vector<VoidPointer> &InArgs) {return false;}
	};
}
