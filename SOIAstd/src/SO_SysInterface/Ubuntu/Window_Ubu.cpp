#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <X11/Xlib.h>
#include "Vector2D.h"
#include "pxPoint.h"
#include "fPoint.h"
#include "Thread.h"
#include "Window_Base.h"
#include "Window_Ubu.h"


using namespace SO;
using namespace SO::Drawing;

////////////////////////////////////////////////////////////////////
// init
Window_Ubu::Window_Ubu() : Window_Base()
{

}
Window_Ubu::~Window_Ubu()
{

}
void Window_Ubu::Start ()
{
	display = XOpenDisplay(NULL);
	visual = DefaultVisual(display, 0);
	depth  = DefaultDepth(display, 0);

	frame_attributes.background_pixel = XWhitePixel(display, 0);
	/* create the application window */
	frame_window = XCreateWindow(display, XRootWindow(display, 0),
								 0, 0, 400, 400, 5, depth,
								 InputOutput, visual, CWBackPixel,
								 &frame_attributes);

	XStoreName(display, frame_window, "Hello World Example");
	XSelectInput(display, frame_window, ExposureMask | StructureNotifyMask);

	XMapWindow(display, frame_window);

	MThread.AddLoops(-1);
	Thread::Start();
}

////////////////////////////////////////////////////////////////////////////////////////////
// ticking
void Window_Ubu::Tick()
{
	char	hello_string[] = "Hello World";
	int    hello_string_length = strlen(hello_string);

	XNextEvent(display, (XEvent *)&event);
	SetVars();
	switch ( event.type )
	{
		case Expose:
			fontinfo = XLoadQueryFont(display, "10x20");
			gr_values.font = fontinfo->fid;
			gr_values.foreground = XBlackPixel(display, 0);
			graphical_context = XCreateGC(display, frame_window, GCFont+GCForeground, &gr_values);

			XWindowAttributes window_attributes;
			int font_direction, font_ascent, font_descent;
			XCharStruct text_structure;

			DrawText(fPoint(0.5, 0.5), string("hallo nochmal"));
			DrawLine(fPoint(), fPoint(1,1));
			break;
		default:
			break;
	}
}
void Window_Ubu::SetVars()
{
	XWindowAttributes window_attributes;
	XGetWindowAttributes(display, frame_window, &window_attributes);
	size = pxPoint(window_attributes.width, window_attributes.height);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// drawing
//---- main routine ----
//void Window_Ubu::Draw()
//{
//
//}
//---- subroutines ----
void Window_Ubu::pxDrawText(pxPoint Loc, const string &text)
{
	XDrawString(display, frame_window, graphical_context,	Loc.X, Loc.Y, text.c_str(), strlen(text.c_str()));
}
void Window_Ubu::pxDrawLine(pxPoint a, pxPoint b)
{
	XDrawLine(display, frame_window, graphical_context, a.X, a.Y, b.X, b.Y);
}


