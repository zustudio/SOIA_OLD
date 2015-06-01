
#pragma once

#include "VoidPointer.h"

#include <vector>

namespace Environment
{
	class LIBIMPEXP ElementReflection
	{
	public:
		ElementReflection(const std::vector<VoidPointer>& InAttributes);

		std::vector<VoidPointer> Attributes;
	};
}