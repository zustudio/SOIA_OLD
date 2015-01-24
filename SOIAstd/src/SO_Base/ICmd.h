
#pragma once

#include <vector>

namespace SO
{
	namespace Base
	{
		class ICmd
		{
		public:
			virtual bool Execute(void* TargetObj, void* Caller, const std::vector<void*> &Args) const = 0;
		};
	}
}