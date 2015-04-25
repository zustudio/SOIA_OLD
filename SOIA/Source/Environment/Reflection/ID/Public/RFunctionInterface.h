
#pragma once

#include "RElement.h"

#include "Environment/Reflection/TypeAttribute/Public/VoidPointer.h"

#include <vector>

namespace Environment
{
	class DLLIMPEXP RFunctionInterface : public RElement
	{
	public:
		virtual bool Execute(const std::vector<SO::Base::VoidPointer> &InArgs) = 0;
	};
}