
#pragma once

#include "VoidPointer.h"

namespace Environment
{
	class ObjectMirror
	{
	public:
		virtual VoidPointer Get() = 0;
		virtual bool SetIfTypesMatch(const VoidPointer& InPointer) = 0;
	};
}
