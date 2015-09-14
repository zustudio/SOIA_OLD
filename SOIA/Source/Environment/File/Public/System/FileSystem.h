
#pragma once

#include "CommonFileSytemAccess.h"

namespace Environment
{
	class LIBIMPEXP FileSystem
	{
	public:
		FileSystem();

		CommonFileSystemAccess* GetAccess();

	private:
		CommonFileSystemAccess* Access;
	};
}