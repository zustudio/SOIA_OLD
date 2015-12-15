#include "UnitTest++.h"

#include "LinuxFileSystemAccess"
using namespace Environment;

TEST(GetCurrentProgramDir)
{
	CommonFileSystemAccess& access = LinuxFileSystemAccess();
	Path path = Path("");
	bool result = access.GetExecutablePath(path);
	CHECK_EQUAL(true, result);
}
