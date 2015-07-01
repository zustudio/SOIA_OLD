
#include "Definitions.h"

#include "Logger.h"
#include "StdDialogue.h"

namespace Environment
{
	Logger GlobalLogger(new StdDialogue());
	LIBIMPEXP Logger* GetLogger()
	{
		return &GlobalLogger;
	}
}