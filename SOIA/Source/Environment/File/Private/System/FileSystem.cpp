
#include "Definitions.h"

#include "FileSystem.h"
using namespace Environment;

#include "WindowsFileSystemAccess.h"

FileSystem::FileSystem()
	:
	Access(new WindowsFileSystemAccess)
{}

Directory FileSystem::GetExecutableDirectory()
{
	Path path = Path("");
	Access->GetExecutablePath(path);
	return Directory(path.StripDotName());
}

CommonFileSystemAccess * FileSystem::GetAccess()
{
	return Access;
}
