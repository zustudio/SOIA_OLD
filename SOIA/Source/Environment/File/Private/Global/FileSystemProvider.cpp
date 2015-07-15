
#include "Definitions.h"

#include "FileSystem.h"

namespace Environment
{
	FileSystem GlobalFileSystem;
	LIBIMPEXP FileSystem* GetFileSystem()
	{
		return &GlobalFileSystem;
	}
}