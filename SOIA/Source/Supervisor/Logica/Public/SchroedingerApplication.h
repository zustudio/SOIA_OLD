
#pragma once

#include "Supervisor/Core/Public/Application.h"


namespace Supervisor
{
	class DLLIMPEXP SchroedingerApplication : public Application
	{
	public:
		virtual void Execute() override;
	};
}