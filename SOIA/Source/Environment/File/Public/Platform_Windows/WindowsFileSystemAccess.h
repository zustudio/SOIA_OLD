
#pragma once

#include "CommonFileSytemAccess.h"

#include "dirent.h"

namespace Environment
{
	class WindowsFileSystemAccess : public CommonFileSystemAccess
	{
		virtual bool GetExecutablePath(Path& OutPath) override;
	};
}