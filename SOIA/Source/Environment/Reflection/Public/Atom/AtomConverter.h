
#pragma once

#include "VoidPointer.h"
#include "AtomConverterHelper.h"

namespace Environment
{
	class RElement;
}

namespace Environment
{
	class LIBIMPEXP AtomConverter
	{
	public:
		virtual bool IsType(const std::string& InTypeName) = 0;
		virtual TypeID GetType() = 0;
		virtual VoidPointer* StringToObject(const std::string& InString) = 0;
		virtual std::string ObjectToString(const VoidPointer& InObject) = 0;
		virtual std::vector<RElement*> ObjectToRElements(VoidPointer& InObject) = 0;
	};
}