
#pragma once

#include "PropertyTag.h"
#include "Environment/Reflection/ID/Public/RElement.h"

#include <vector>

namespace Environment
{
	class FileObject
	{
	public:
		////////////////////////////////////////////////////////////////
		// Functions
		//----- Initializing -----
		static FileObject FromTags(const std::vector<PropertyTag> InTags);
		/// Constructor


	};
}