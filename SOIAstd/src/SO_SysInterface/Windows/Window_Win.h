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
		//Window_Win();
		Window_Win(const std::string &NewTitle, const pxPoint &size);
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

///////////////////////////////////////////////////
// macros
//---- color drawing ----
/* prepares the hdc for drawing (the colors are taken from prop.*color) */
#define Win32_PrepDrawing(hdc) { \
	hdc = ::GetDC(hwnd); \
	HGDIOBJ Win32StandardPen = nullptr; \
	HGDIOBJ Win32StandardBrush = nullptr; \
	SelectObject(hdc, GetStockObject(DC_PEN)); \
	SelectObject(hdc, GetStockObject(DC_BRUSH)); \
	SetDCBrushColor(hdc, getColor(props.backColor)); \
	SetDCPenColor(hdc, getColor(props.frontColor)); \
}
#define Win32_EndDrawing(hdc) ::ReleaseDC(hwnd, hdc);
