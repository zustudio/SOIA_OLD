
#pragma once

#include "Environment/Reflection/ID/Public/RContainer.h"

namespace Supervisor
{
	class DLLIMPEXP ServiceProvider
	{
	public:
		////////////////////////////////////////////////////////////////
		// Functions
		//----- Intializing -----

		/// Constructor.
		ServiceProvider();

		////////////////////////////////////////////////////////////////
		// Variables

		Environment::RContainer Services;


	};
}