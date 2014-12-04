#pragma once

#include <X11/Xlib.h>
#include "Window_Base.h"

namespace SO
{
	class Window_Ubu : public SO::Window_Base
	{
	public:
		///////////////////////////////////////////////////////////////////
		// vars
		//---- my instances ----
		Display                 *display;
		Visual                  *visual;
		int                     depth;
		XKeyEvent               event;
		XFontStruct             *fontinfo;
		XSetWindowAttributes    frame_attributes;
		Window                  frame_window;
		int                     text_x;
		int                     text_y;
	    GC                      graphical_context;
		XGCValues               gr_values;

		//////////////////////////////////////////////////////////////////
		// functions
		//---- init ----
	    Window_Ubu();
	    ~Window_Ubu();
		virtual void Start() override;
		//---- loop ----
		virtual void Tick() override;

		void TEST();
	};
}
