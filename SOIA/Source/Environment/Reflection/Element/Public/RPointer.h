
#pragma once

#include "Environment/Reflection/Atomic/Public/Atom.h"

#include "Element_ID.h"
#include "Environment/Reflection/Type/Public/TypeID.h"
#include "Environment/Reflection/Type/Public/VoidPointer.h"

namespace Environment
{
	class RElement;
	class RContainer;
	class DLLIMPEXP RPointer : public Atom
	{
	public:
		RPointer(RElement*,const TypeID& InTypeID);
		RPointer(int InID,const TypeID& InTypeID);

		static std::string ToString(const RPointer& InObject);
		static RPointer FromString(const std::string& InString);

		RElement* Resolve();
		VoidPointer ToVoidPointer();
		
		RContainer* Container;
		Element_ID Target;
		TypeID Type;
	};
}