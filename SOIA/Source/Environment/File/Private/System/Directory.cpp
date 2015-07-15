
#include "Definitions.h"

#include "Directory.h"
using namespace Environment;

#include "FileSystemProvider.h"
#include "CommonFileSytemAccess.h"

Directory::Directory(const Path& InPath)
	:
	PathToDir(InPath)
{}

std::vector<Directory> Directory::GetSubDirectories()
{
	std::vector<Path> outPaths;
	std::vector<Directory> result;
	GetFileSystem()->GetAccess()->GetSubDirectoryPaths(PathToDir, outPaths);

	for (auto path : outPaths)
	{
		result.push_back(Directory(path));
	}
	return result;
}

Path const& Directory::GetPath() const
{
	return PathToDir;
}
