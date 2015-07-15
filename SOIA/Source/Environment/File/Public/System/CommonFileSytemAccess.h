
#pragma once

#include "Path.h"

#include <string>
#include <vector>

namespace Environment
{
	class CommonFileSystemAccess
	{
	public:
		bool GetSubDirectoryPaths(const Path& InDir, std::vector<Path>& OutPaths);
		bool GetFilePaths(const Path& InDir, std::vector<Path>& OutPaths);

		virtual bool GetExecutablePath(Path& OutPath) = 0;

	private:
		bool ReadDirectory(const Path& InDir, int Type, std::vector<Path>& OutPaths);
		//virtual bool GetExecutableDirectory(const std::string& OutDir) = 0;
		//virtual bool CreateDirectory(const std::string& InDir) = 0;
	};
}