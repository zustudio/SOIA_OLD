#pragma once 

#include <string>
#include <deque>

#include "Thread.h"
#include "fPoint.h"
#include "pxPoint.h"

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
		virtual void DrawText(fPoint Loc, const std::string &text);
		virtual void DrawLine(fPoint a, fPoint b);
		virtual void DrawRect(fPoint a, fPoint b);

		virtual void pxDrawText(pxPoint Loc, const std::string &text);
		virtual void pxDrawLine(pxPoint a, pxPoint b);
		virtual void pxDrawRect(pxPoint a, pxPoint b);
	};
}
