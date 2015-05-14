
#pragma once

#include "Environment/Reflection/Type/Public/VoidPointer.h"

namespace Environment
{
	class DLLIMPEXP AtomReflection
	{
	public:
		virtual bool IsType(const std::string& InTypeName) = 0;
		virtual VoidPointer* StringToObject(const std::string& InString) = 0;
		virtual std::string ObjectToString(VoidPointer& InObject) = 0;
		std::string GetAtomString(VoidPointer& InAtom);
	};
}