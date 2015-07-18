
#include "Definitions.h"

#include "File.h"
using namespace Environment;

File::File(Path const & InPathToFile)
	:
	PathToFile(InPathToFile)
{}

Path File::GetPath() const
{
	return PathToFile;
}

