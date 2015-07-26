
#include "Definitions.h"

#include "RContainer.h"

namespace Environment
{
	RContainer* CurrentContainer;
	LIBIMPEXP RContainer* GlobalContainer()
	{
		return CurrentContainer;
	}
	LIBIMPEXP void SetGlobalContainer(RContainer* InContainer)
	{
		CurrentContainer = InContainer;
	}

}