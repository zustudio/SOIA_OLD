
#pragma once

#include "Environment/Reflection/Type/Public/VoidPointer.h"

#include <string>

namespace Environment
{
	class DLLIMPEXP PropertyTag
	{
	public:
		PropertyTag(VoidPointer* InObject, const std::string& InTypeString, const std::string& InContentString);
		std::string CompleteString;
		std::string TypeString;
		std::string ContentString;
		VoidPointer* Object;
	};
}