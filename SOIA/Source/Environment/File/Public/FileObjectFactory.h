
#pragma once

#include "FileObject.h"

namespace Environment
{
	class FileObjectFactory
	{
	public:

		FileObject FromTags(const std::vector<PropertyTag>& InTags);
		FileObject FromObject(RElement* InObject);
	};
}