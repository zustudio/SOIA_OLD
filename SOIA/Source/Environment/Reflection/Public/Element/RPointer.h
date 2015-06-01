
#pragma once

#include "Atom.h"

#include "Element_ID.h"
#include "TypeID.h"
#include "VoidPointer.h"

namespace Environment
{
	class RElement;
	class RContainer;
	class LIBIMPEXP RPointer : public Atom
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