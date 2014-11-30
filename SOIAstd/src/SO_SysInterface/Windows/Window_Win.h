#pragma once

#include <windows.h>
#include "Window_Base.h"

namespace SO
{
	class Window_Win : public Window_Base
	{
	public:
		//////////////////////////////////////////////////
		// functions
		//---- init ----
		Window_Win();
		~Window_Win();
		//---- loop ----
		virtual void Start() override;
	};
}