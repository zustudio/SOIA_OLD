
#include "Definitions.h"

#include "CommonFileSytemAccess.h"
using namespace Environment;

#include "dirent.h"

bool CommonFileSystemAccess::GetSubDirectoryPaths(const Path & InDir, std::vector<Path>& OutPaths)
{
	return ReadDirectory(InDir, DT_DIR, OutPaths);
}

bool CommonFileSystemAccess::GetFilePaths(const Path& InDir, std::vector<Path>& OutPaths)
{
	return ReadDirectory(InDir, DT_REG, OutPaths);
}

bool CommonFileSystemAccess::ReadDirectory(const Path & InPath, int IntType, std::vector<Path>& OutPaths)
{
	bool success = false;

	DIR* p_dir = nullptr;
	dirent* p_dirent = nullptr;
	p_dir = opendir(InPath.ToString().c_str());

	if (p_dir)
	{
		while (p_dirent = readdir(p_dir))
		{
			if (p_dirent->d_type == IntType)
			{
				Path foundPath = Path("");

				if (p_dirent->d_type == DT_DIR)
					foundPath = InPath.AppendFolder(p_dirent->d_name);
				else
					foundPath = InPath.AppendFile(p_dirent->d_name);

				OutPaths.push_back(foundPath);
			}
		}
		success = true;
	}
	return success;
}
