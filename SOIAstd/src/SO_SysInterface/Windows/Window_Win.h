#pragma once

#include <windows.h>
#include "Window_Base.h"

namespace SO
{
	class Window_Win : public Window_Base
	{
	public:
		//////////////////////////////////////////////////
		// vars
		//---- instances ----
		HWND hwnd;

		//////////////////////////////////////////////////
		// functions
		//---- init ----
		Window_Win();
		~Window_Win();
		virtual void Start() override;
		//---- loop ----
		virtual void Tick() override;
			virtual void SetVars() override;
		//---- drawing ----
		virtual void pxDrawText(pxPoint Loc, const std::string &text) override;
		virtual void pxDrawLine(pxPoint a, pxPoint b) override;
		virtual void pxDrawRect(pxPoint a, pxPoint b) override;
	};
}