
#pragma once

#include "Graphics/Core/Public/Window.h"

namespace Supervisor
{
	class DLLIMPEXP Application
	{
	public:
		virtual void Execute() = 0;

		SO::Window* MainWindow;
	};
}