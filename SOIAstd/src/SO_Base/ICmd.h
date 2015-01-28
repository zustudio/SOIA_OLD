
#pragma once

#include <vector>
#include "VoidPointer.h"

namespace SO
{
	namespace Base
	{
		class ICmd
		{
		public:
			virtual bool Execute(void* TargetObj, void* Caller, const std::vector<VoidPointer> &Args) const = 0;
		};
	}
}