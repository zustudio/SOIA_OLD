
#pragma once

#include "Element_ID.h"
#include "Environment/Reflection/TypeAttribute/Public/VoidPointer.h"

namespace Environment
{
	class RElement;
	class RContainer;
	class DLLIMPEXP RPointer
	{
	public:
		RPointer(RElement*,const std::string& InTypeID);
		RPointer(int InID,const std::string& InTypeID);
		RElement* Resolve();
		VoidPointer ToVoidPointer();
		
		RContainer* Container;
		Element_ID Target;
		std::string Type;
	};
}