
#include "Definitions.h"

#include "FileSystem.h"
using namespace Environment;

#include "WindowsFileSystemAccess.h"

FileSystem::FileSystem()
	:
	Access(new WindowsFileSystemAccess)
{}

CommonFileSystemAccess * FileSystem::GetAccess()
{
	return Access;
}
