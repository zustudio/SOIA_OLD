
#pragma once

#include "Environment/Reflection/TypeAttribute/Public/VoidPointer.h"

namespace Environment
{
	class AtomReflectionInterface
	{
	public:
		virtual bool IsType(const std::string& InTypeName) = 0;
		virtual VoidPointer* StringToObject(const std::string& InString) = 0;
		virtual std::string ObjectToString(const VoidPointer& InObject) = 0;
	};
}