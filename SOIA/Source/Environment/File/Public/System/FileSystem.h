
#pragma once

#include "Directory.h"
#include "CommonFileSytemAccess.h"

namespace Environment
{
	class LIBIMPEXP FileSystem
	{
	public:
		FileSystem();

		Directory GetExecutableDirectory();

		CommonFileSystemAccess* GetAccess();

	private:
		CommonFileSystemAccess* Access;
	};
}