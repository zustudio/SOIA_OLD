
#pragma once

#include "PropertyTag.h"
#include "Environment/Reflection/Element/Public/RElement.h"

#include <vector>

namespace Environment
{
	class DLLIMPEXP FileObject
	{
	public:
		////////////////////////////////////////////////////////////////
		// Functions
		//----- Initializing -----
		
		/// Constructor
		FileObject(RClass* InClass, const std::vector<VoidPointer>& InAttributes);

		VoidPointer* CreateObject();

		RClass* Class;
		std::vector<VoidPointer> Attributes;

	};
}