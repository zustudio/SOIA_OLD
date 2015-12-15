
#include "Definitions.h"

#include "LinuxFileSystemAccess.h"
using namespace Env;

#include <iostream>
#include <regex>

#include <unistd.h>
#include <limits.h>


bool LinuxFileSystemAccess::GetExecutablePath(Path& OutPath)
{
	char buf[PATH_MAX];
	int size = ::readlink("/proc/self/exe", buf, 256);
	if (size != -1)
	{
		buf[size] = '\0';
	}
	std::string fullPath = std::string(buf);
	std::string onlyPath;
	
	std::regex regex = std::regex("(.*/)[^/]*");
	auto match = std::smatch();
	bool result = std::regex_match(fullPath, match, regex);
	if (result)
	{
		onlyPath = match[1];
		std::cout << onlyPath << std::endl;
	}
	
	OutPath = Path(onlyPath);
	return true;
}

bool LinuxFileSystemAccess::CreatePathDirectory(Path const & InPath)
{
	return false;
}
