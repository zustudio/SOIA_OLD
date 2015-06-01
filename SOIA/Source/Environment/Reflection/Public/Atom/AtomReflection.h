
#pragma once

#include "VoidPointer.h"

namespace Environment
{
	class RElement;
	class RClass;
	class LIBIMPEXP AtomReflection
	{
	public:
		virtual bool IsType(const std::string& InTypeName) = 0;
		virtual VoidPointer* StringToObject(const std::string& InString) = 0;
		virtual std::string ObjectToString(VoidPointer& InObject) = 0;
		virtual std::vector<RElement*> ObjectToRElements(VoidPointer& InObject);
		std::string GetAtomString(VoidPointer& InAtom);
		VoidPointer* GetAtomObject(const std::string& InString, const TypeID& InType);
		RClass* GetReflectedClass(const TypeID& InID);
	};
}