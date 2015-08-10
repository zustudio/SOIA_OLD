
#pragma once

#include "VoidPointer.h"

namespace Environment
{
	class LIBIMPEXP ObjectMirror
	{
	public:
		explicit ObjectMirror(const std::string& InName);

		virtual VoidPointer Object() = 0;
		virtual TypeID ObjectType() = 0;
		virtual bool SetIfTypesMatch(const VoidPointer& InPointer) = 0;

		std::string Name;
	};
}
