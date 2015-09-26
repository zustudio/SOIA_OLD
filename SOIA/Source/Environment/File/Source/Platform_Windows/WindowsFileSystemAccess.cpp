
#include "Definitions.h"

#include "WindowsFileSystemAccess.h"
using namespace Environment;

#include "dirent.h"

bool WindowsFileSystemAccess::GetExecutablePath(Path& OutPath)
{
	bool success = false;
	char pBuf[256];
	int len = 255;
	int bytes = GetModuleFileName(NULL, pBuf, len);
	if (bytes > 0)
	{
		pBuf[bytes] = 0;
		OutPath = Path(std::string(pBuf));
		success = true;
	}
	return success;
}

bool WindowsFileSystemAccess::CreatePathDirectory(Path const& InPath)
{
	return (CreateDirectory(InPath.ToString().c_str(), NULL) || ERROR_ALREADY_EXISTS);
}
