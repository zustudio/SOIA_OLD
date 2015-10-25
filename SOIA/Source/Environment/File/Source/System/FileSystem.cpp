
#include "Definitions.h"

#include "FileSystem.h"
using namespace Environment;

#ifdef def_BUILD_OS__Windows
#include "WindowsFileSystemAccess.h"
#define FILE_SYSTEM_ACCESS WindowsFileSystemAccess
#else
#include "LinuxFileSystemAccess.h"
#define FILE_SYSTEM_ACCESS LinuxFileSystemAccess
#endif

FileSystem::FileSystem()
	:
	Access(new FILE_SYSTEM_ACCESS)
{}

CommonFileSystemAccess * FileSystem::GetAccess()
{
	return Access;
}
