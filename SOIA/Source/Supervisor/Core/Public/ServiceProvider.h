
#pragma once

#include "Environment/Reflection/Element/Public/RContainer.h"

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