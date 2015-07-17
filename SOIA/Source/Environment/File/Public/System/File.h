
#pragma once

#include "Path.h"

namespace Environment
{
	class File
	{
	public:
		File(Path const& InPathToFile);

		Path PathToFile;
	};
}