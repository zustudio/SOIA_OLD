
#pragma once

#include "Environment/Reflection/Type/Public/VoidPointer.h"

#include <vector>

namespace Environment
{
	class DLLIMPEXP ElementReflection
	{
	public:
		ElementReflection(const std::vector<VoidPointer>& InAttributes);

		std::vector<VoidPointer> Attributes;
	};
}