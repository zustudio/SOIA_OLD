#pragma once 

#include <string>
#include <deque>

#include "Thread.h"
#include "fPoint.h"
#include "pxPoint.h"

using namespace SO::Drawing;

namespace SO
{
	class Window_Base : public Thread
	{
	public:
		//////////////////////////////////////////
		//---- properties ----
		Drawing::pxPoint size;

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
