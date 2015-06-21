
#pragma once

#include "PropertyTag.h"
#include "RElement.h"
#include "RContainer.h"

#include <vector>

namespace Environment
{
	class LIBIMPEXP FileObject
	{
	public:
		////////////////////////////////////////////////////////////////
		// Functions
		//----- Initializing -----
		
		/// Constructor
		FileObject(RClass* InClass, const std::vector<VoidPointer*>& InAttributes);

		VoidPointer* CreateObject();
		VoidPointer* ResolvePointers(RContainer* InContainer);

		RClass* Class;
		std::vector<VoidPointer*> Attributes;

	private:
		VoidPointer* Object;
		bool bIsReflected;

	};
}