
#pragma once

#include "RElement.h"

namespace Supervisor
{
	RCLASS(RGUI, Environment::RElement);
	class LIBIMPEXP RGUI : public RGUI_Base
	{
		RCLASS_BEGIN();

		RGUI();

		void Start();

		RCLASS_END();
	};
}