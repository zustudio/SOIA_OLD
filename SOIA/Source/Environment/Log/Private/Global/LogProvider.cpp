
#include "Definitions.h"

#include "Logger.h"
#include "StdDialogue.h"

namespace Environment
{
	Logger CurrentLogger(new StdDialogue());
	LIBIMPEXP Logger* GlobalLogger()
	{
		return &CurrentLogger;
	}
	LIBIMPEXP void SetGlobalLogger(Logger const& InLogger)
	{
		CurrentLogger = InLogger;
	}
}