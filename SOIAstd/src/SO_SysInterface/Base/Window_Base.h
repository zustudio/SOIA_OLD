#pragma once 

#include "Thread.h"

namespace SO
{
	class Window_Base : public Thread
	{
	public:
		//////////////////////////////////////////
		// functions
		//---- init ----
		Window_Base();
		~Window_Base();
		//---- main ----
		virtual void Start() override;
	};
}