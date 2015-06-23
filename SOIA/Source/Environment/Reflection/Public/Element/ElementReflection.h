
#pragma once

#include "VoidPointer.h"

#include <vector>

namespace Environment
{
	class LIBIMPEXP ElementReflection
	{
	public:
		explicit ElementReflection(const std::vector<VoidPointer>& InAttributes);
		explicit ElementReflection(const std::vector<VoidPointer*>& InAttributes);

		std::vector<VoidPointer> Attributes;
	};
}