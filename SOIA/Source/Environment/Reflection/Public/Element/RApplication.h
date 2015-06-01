
#pragma once

// include super classes
#include "RService.h"
#include "Environment/Thread/Public/Thread.h"

namespace Environment
{
	class LIBIMPEXP RApplication : public RService, public Environment::Thread
	{
	public:
		RApplication(Environment::RContainer& InServiceContainer);

	};
}
