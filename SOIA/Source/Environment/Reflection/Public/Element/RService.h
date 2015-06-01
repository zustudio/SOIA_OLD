
#pragma once

// include super class
#include "RContainer.h"

// include SOIA


namespace Environment
{
	class RService : public Environment::RContainer
	{
	public:
		RService(Environment::RContainer &InServices);

		Environment::RContainer* Services;
	};
}
