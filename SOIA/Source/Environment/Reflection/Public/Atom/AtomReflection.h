
#pragma once

#include "VoidPointer.h"
#include "Element_ID.h"

namespace Environment
{
	class RElement;
	class RContainer;
	class RClass;
	class LIBIMPEXP AtomReflection
	{
	public:
		AtomReflection() {};
		virtual ~AtomReflection() {};

		virtual bool IsType(const std::string& InTypeName) = 0;
		virtual VoidPointer* StringToObject(const std::string& InString) = 0;
		virtual std::string ObjectToString(const VoidPointer& InObject) = 0;
		virtual std::vector<RElement*> ObjectToRElements(VoidPointer& InObject);
		static std::string GetAtomString(const VoidPointer& InAtom);
		static VoidPointer* GetAtomObject(const std::string& InString, const TypeID& InType);
		static RElement* GetElementByID(const Element_ID& InID, RContainer* InContainer);
		RClass* GetReflectedClass(const TypeID& InID);
	};
}