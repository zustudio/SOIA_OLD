
#pragma once

#include "RElement.h"

#include "Environment/Reflection/Type/Public/VoidPointer.h"

#include <vector>

namespace Environment
{
	class DLLIMPEXP RFunctionInterface : public RElement
	{
	public:
		virtual bool Execute(const std::vector<VoidPointer> &InArgs) = 0;
	};
}