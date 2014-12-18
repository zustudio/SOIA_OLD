#pragma once 

#include <string>
#include <deque>

#include "Thread.h"
#include "cPoint.h"
#include "pxPoint.h"
#include "cPoint.h"

using namespace SO::Drawing;

namespace SO
{
	namespace Drawing
	{
		class fColor;
	}

	class Window_Base : public Thread
	{
	public:
		//////////////////////////////////////////
		//---- properties ----
		struct WindowProperties
		{
			Drawing::pxPoint size;
			Drawing::fColor* backColor;
			Drawing::fColor* frontColor;
			Drawing::fColor* copyBackC;
			Drawing::fColor* copyFrontC;
			bool bDirty;					//true if window needs to be redrawn

		};
		WindowProperties props;

		//////////////////////////////////////////
		// functions
		//---- init ----
		Window_Base();
		~Window_Base();
		//---- main ----
		virtual void Start() override;
		//---- loop ----
		virtual void Tick() override;		//functions below can be called from tick, if events are raised
			virtual void SetVars();
			virtual void Draw();
		//////////////////////////////////////////
		// utility functions
		//---- drawing ----
		virtual void DrawText(cPoint Loc, const std::string &text, fColor *frontColor = nullptr, fColor *backColor = nullptr);
		virtual void DrawLine(cPoint a, cPoint b, fColor *frontColor = nullptr, fColor *backColor = nullptr);
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
