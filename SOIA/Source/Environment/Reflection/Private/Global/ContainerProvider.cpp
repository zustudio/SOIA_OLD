
#include "Definitions.h"

#include "RContainer.h"

namespace Environment
{
	RContainer* TopContainer;
	LIBIMPEXP RContainer* GetTopContainer()
	{
		return TopContainer;
	}
	LIBIMPEXP void SetTopContainer(RContainer* InContainer)
	{
		TopContainer = InContainer;
	}

}