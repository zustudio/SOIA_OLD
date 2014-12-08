#include "stdafx.h"
#include "Window_Base.h"

using namespace SO;
using namespace std;

///////////////////////////////////////////////////
// init
Window_Base::Window_Base()
{

}
Window_Base::~Window_Base()
{

}

///////////////////////////////////////////////////
// main
void Window_Base::Start()
{
	std::cout << "Window class: application compiled without window interface, exiting.";
}
//////////////////////////////////////////////////
// ticking loop
void Window_Base::Tick()
{
	/*this function has to be implemented in base classes
	 * supposed behaviour:
	 * 		1	wait for event
	 * 		2	call SetVariables
	 * 		3	call Draw (if needed)
	 * 		n	call nth functions (if needed)
	 */
}
void Window_Base::SetVars()
{
	/*
	 * please set following variables:
	 * 		1	size
	 */
}
void Window_Base::Draw() {}

/////////////////////////////////////////////////////////////////////////////////////////////
// basic drawing interface
void Window_Base::DrawText(fPoint Loc, const string &text)
{
	pxPoint px =	Loc.ToPxPoint(size);
	pxDrawText(px, text);
}
void Window_Base::DrawLine(fPoint a, fPoint b)
{
	pxPoint pxA = a.ToPxPoint(size);
	pxPoint pxB = b.ToPxPoint(size);
	pxDrawLine(pxA, pxB);
}
void Window_Base::DrawRect(fPoint a, fPoint b)
{
	pxPoint pxA = a.ToPxPoint(size);
	pxPoint pxB = b.ToPxPoint(size);
	pxDrawRect(pxA, pxB);
}
// functions to be implemented
void Window_Base::pxDrawText(pxPoint Loc,const string& text){}
void Window_Base::pxDrawLine(pxPoint a, pxPoint b) {}
void Window_Base::pxDrawRect(pxPoint a, pxPoint b) {}

