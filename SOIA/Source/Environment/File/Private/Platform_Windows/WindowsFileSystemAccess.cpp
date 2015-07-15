
#include "Definitions.h"

#include "WindowsFileSystemAccess.h"
using namespace Environment;

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
