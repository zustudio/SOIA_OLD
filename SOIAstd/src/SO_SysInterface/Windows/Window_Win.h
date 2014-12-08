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
		virtual void Start() override;
		//---- loop ----
		virtual void Tick() override;
	};
}