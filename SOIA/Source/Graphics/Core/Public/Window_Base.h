#pragma once

#include <string>
#include <iostream>

#include "Graphics/DataStructures/Public/fColor.h"
#include "Graphics/DataStructures/Public/cPoint.h"
#include "Graphics/DataStructures/Public/pxPoint.h"

using namespace Graphics;

namespace SO
{
	class DLLIMPEXP Window_Base
	{
	public:
		//////////////////////////////////////////
		//---- properties ----
		struct WindowProperties
		{
			std::string* title;
			pxPoint size;
			fColor* backColor;
			fColor* frontColor;
			fColor* copyBackC;
			fColor* copyFrontC;
			bool bDirty;					//< true if window needs to be redrawn
			bool bOpen;						//< true, if window is currently open

		};
		WindowProperties props;

		//////////////////////////////////////////
		// functions
		//---- init ----
		Window_Base(const std::string &NewTitle, const pxPoint &size);
		virtual ~Window_Base();
		//---- main ----
		virtual int Open();
		//---- loop ----
		virtual void Tick();		//functions below can be called from tick, if events are raised
			virtual void SetVars();
			virtual void Draw();
		//////////////////////////////////////////
		// utility functions
		//---- drawing ----
		virtual void Refresh();

		virtual void DrawText(cPoint Loc, const std::string &text, fColor *frontColor = nullptr, fColor *backColor = nullptr);
		virtual void DrawLine(cPoint a, cPoint b, fColor *frontColor = nullptr, fColor *backColor = nullptr);
		virtual void DrawArrow(cPoint a, cPoint b, fColor *frontColor = nullptr, fColor *backColor = nullptr);
		virtual void DrawRect(cPoint a, cPoint b, fColor *frontColor = nullptr, fColor *backColor = nullptr);

		virtual void pxDrawText(pxPoint Loc, const std::string &text);
		virtual void pxDrawLine(pxPoint a, pxPoint b);
		virtual void pxDrawRect(pxPoint a, pxPoint b);

		//////////////////////////////////////////
		// private helpers
	private:
		//---- drawing ----
		void SetColors(fColor *front, fColor *back);
		void ResetColors();
	};
}
