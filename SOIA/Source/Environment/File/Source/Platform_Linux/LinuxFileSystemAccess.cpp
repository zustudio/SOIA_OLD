
#include "Definitions.h"

#include "LinuxFileSystemAccess.h"
using namespace Env;

#include <iostream>

bool LinuxFileSystemAccess::GetExecutablePath(Path& OutPath)
{
	OutPath = Path("/mu");
	return false;
}

bool LinuxFileSystemAccess::CreatePathDirectory(Path const & InPath)
{
	return false;
}
