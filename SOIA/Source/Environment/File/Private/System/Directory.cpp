
#include "Definitions.h"

#include "Directory.h"
using namespace Environment;

#include "FileSystemProvider.h"
#include "CommonFileSytemAccess.h"

Directory::Directory(const Path& InPath)
	:
	PathToDir(InPath)
{}

Directory Directory::ExecutableDirectory()
{
	Path path = Path("");
	GetFileSystem()->GetAccess()->GetExecutablePath(path);
	return Directory(path.StripDotName());
}

bool Directory::Create()
{
	return GetFileSystem()->GetAccess()->CreatePathDirectory(PathToDir);
}

std::vector<Directory> Directory::GetSubDirectories(EDirectoryVisibility InDirVisibility) const
{
	std::vector<Path> outPaths;
	std::vector<Directory> result;
	GetFileSystem()->GetAccess()->GetSubDirectoryPaths(PathToDir, outPaths);

	for (auto path : outPaths)
	{
		if (InDirVisibility == EDirectoryVisibility::NotSystem
			&& (path.GetName() == "." || path.GetName() == ".."))
		{
			continue;
		}
		else
		{
			result.push_back(Directory(path));
		}
	}
	return result;
}

Path const& Directory::GetPath() const
{
	return PathToDir;
}

std::string Directory::StaticToString(const Directory & InObject)
{
	return InObject.GetPath().ToString();
}

Directory Directory::StaticToObject(const std::string & InString)
{
	return Directory(Path(InString));
}