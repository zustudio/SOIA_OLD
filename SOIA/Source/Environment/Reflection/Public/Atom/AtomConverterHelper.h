
#pragma once

#include "VoidPointer.h"
#include "ElementID.h"

#include <string>

namespace Environment
{
	class RElement;
	class RContainer;
	class RClass;
}

namespace Environment
{
	class LIBIMPEXP AtomConverterHelper
	{
	public:
		static std::string GetAtomString(const VoidPointer& InAtom);
		static VoidPointer* GetAtomObject(const std::string& InString, const TypeID& InType);
		static RElement* GetElementByID(const ElementID& InID, RContainer* InContainer);
		static RClass* GetReflectedClass(const TypeID& InID);
	};
}