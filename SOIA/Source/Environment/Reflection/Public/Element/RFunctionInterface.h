
#pragma once

#include "RElement.h"

#include "VoidPointer.h"

#include <vector>

namespace Environment
{
	class LIBIMPEXP RFunctionInterface : public RElement
	{
	public:
		virtual bool Execute(const std::vector<VoidPointer> &InArgs) {return false;}
	};
}
