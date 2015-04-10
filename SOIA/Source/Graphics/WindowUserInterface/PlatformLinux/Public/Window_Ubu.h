#pragma once

#include <X11/Xlib.h>
#include "Window_Base.h"

namespace SO
{
	class Window_Ubu : public SO::Window_Base
	{
	private:
		///////////////////////////////////////////////////////////////////
		// vars
		//---- my instances ----
		Display                 *display;
		Visual                  *visual;
		int                     depth;
		//XKeyEvent               event;
		XFontStruct             *fontinfo;
		XSetWindowAttributes    frame_attributes;
		Window                  frame_window;
		int                     text_x;
		int                     text_y;
	    GC                      graphical_context;
		XGCValues               gr_values;

		/* This is used to intercept window closing requests.  */
			 Atom wm_delete_window;


		//////////////////////////////////////////////////////////////////
		// functions
	public:
		//---- init ----
	    Window_Ubu(const std::string &NewTitle, const pxPoint &size);
	    ~Window_Ubu();
		virtual int Init() override;
		//---- loop ----
		virtual void Tick() override;
			void DispatchMessage();
			virtual void SetVars() override;
		//---- utility functions ----
	public:
		virtual void Refresh() override;
		virtual void pxDrawText(pxPoint Loc, const std::string &text) override;
		virtual void pxDrawLine(pxPoint a, pxPoint b) override;
		virtual void pxDrawRect(pxPoint a, pxPoint b) override;
		//---- private helper functions ----
	private:
		XColor getColor(fColor *color);
		//void XLib_PrepDraw();
	};
}
		//---- helper macros ----
		#define XLib_PrepDrawing(fcolor) { \
			Colormap cmap = DefaultColormap(display, DefaultScreen(display)); \
			XColor color = getColor(fcolor); \
			color.flags = DoRed | DoGreen | DoBlue; \
			XAllocColor(display, cmap, &color); \
			XSetForeground(display, graphical_context, color.pixel); \
		}



