#pragma once

#include <windows.h>
#include "Window_Base.h"

namespace SO
{
	//forward declarations
	namespace Drawing
	{
		class fColor;
	}

	//class:
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
		//---- windows ----
		static LRESULT CALLBACK WindowProcedure(HWND window, unsigned int msg, WPARAM wp, LPARAM lp);
		//---- loop ----
		virtual void Tick() override;
			virtual void SetVars() override;
		//---- drawing ----
		virtual void pxDrawText(pxPoint Loc, const std::string &text) override;
		virtual void pxDrawLine(pxPoint a, pxPoint b) override;
		virtual void pxDrawRect(pxPoint a, pxPoint b) override;
		//---- sub drawing ----
		COLORREF getColor(fColor* color);
		void Clear();
	};
}