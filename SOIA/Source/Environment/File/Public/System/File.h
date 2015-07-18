
#pragma once

#include "Path.h"

namespace Environment
{
	class LIBIMPEXP File
	{
	public:
		File(Path const& InPathToFile);

		Path GetPath() const;
	protected:
		Path PathToFile;
	};
}