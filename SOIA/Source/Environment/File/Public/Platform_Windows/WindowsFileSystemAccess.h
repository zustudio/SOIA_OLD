
#pragma once

#include "CommonFileSytemAccess.h"

namespace Environment
{
	class WindowsFileSystemAccess : public CommonFileSystemAccess
	{
		virtual bool GetExecutablePath(Path& OutPath) override;
		virtual bool CreatePathDirectory(const Path& InPath) override;
	};
}