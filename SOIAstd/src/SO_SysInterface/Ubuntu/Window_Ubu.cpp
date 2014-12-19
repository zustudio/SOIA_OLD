#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <X11/Xlib.h>
#include "Vector2D.h"
#include "pxPoint.h"
#include "fPoint.h"
#include "fColor.h"
#include "Thread.h"
#include "Window_Base.h"
#include "Window_Ubu.h"


using namespace SO;
using namespace SO::Drawing;

using namespace std;

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

	//disable not wanted closing of window by standard windowmanager:
	XMapWindow(display, frame_window);
	wm_delete_window = XInternAtom(display, "WM_DELETE_WINDOW", False);
	XSetWMProtocols(display, frame_window, &wm_delete_window, 1);

	//start and end of loop
	MThread.AddLoops(-1);
	Thread::Start();
	XCloseDisplay(display);
}

////////////////////////////////////////////////////////////////////////////////////////////
// ticking
void Window_Ubu::Tick()
{
	DispatchMessage();
	if (props.bDirty)
	{
		SetVars();
		Draw();
		props.bDirty = false;
	}
}
void Window_Ubu::DispatchMessage()
{
	XEvent event;
	XNextEvent(display, &event);
		switch ( event.type )
		{
			case Expose:
				props.bDirty = true;
				break;
			case ClientMessage:
				if ((Atom)event.xclient.data.l[0] == wm_delete_window)
				{
					MThread.Disable();
				}
				break;
			default:
				break;
		}
}
void Window_Ubu::SetVars()
{
	//needed:?
	fontinfo = XLoadQueryFont(display, "10x20");
				gr_values.font = fontinfo->fid;
				gr_values.foreground = XBlackPixel(display, 0);
				graphical_context = XCreateGC(display, frame_window, (unsigned long) 0, &gr_values);
	XSetFillStyle(display, graphical_context, FillSolid);

	XWindowAttributes window_attributes;
	XGetWindowAttributes(display, frame_window, &window_attributes);
	props.size = pxPoint(window_attributes.width, window_attributes.height);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// drawing
//---- subroutines ----
void Window_Ubu::pxDrawText(pxPoint Loc, const string &text)
{
	XDrawString(display, frame_window, graphical_context,	Loc.X, Loc.Y, text.c_str(), strlen(text.c_str()));
}
void Window_Ubu::pxDrawLine(pxPoint a, pxPoint b)
{
	XDrawLine(display, frame_window, graphical_context, a.X, a.Y, b.X, b.Y);
}
void Window_Ubu::pxDrawRect(pxPoint a, pxPoint b)
{
//	XColor frontColor;
//	XColor backColor;
//	Colormap cmap;
	XLib_PrepDrawing(props.frontColor);
	XFillRectangle(display, frame_window, graphical_context, a.X, a.Y, b.X, b.Y);
	XLib_PrepDrawing(props.backColor);
	XDrawRectangle(display, frame_window, graphical_context, a.X, a.Y, b.X, b.Y);
}

//---- private helper functions ----
XColor Window_Ubu::getColor(fColor *color)
{
	XColor newColor;
	newColor.red = 65535 * color->R;
	newColor.green = 65535 * color->G;
	newColor.blue = 65535 * color->B;
	return newColor;
}
//void Window_Ubu::XLib_PrepDraw()
//{
//	XColor frontColor;
//	XColor backColor;
//
//
//
//}


