
#pragma once

// include super class
#include "Environment/Reflection/ID/Public/RContainer.h"

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
