#include "stdafx.h"

#include "Window_Base.h"

using namespace SO;
using namespace std;

///////////////////////////////////////////////////
// init
Window_Base::Window_Base(const std::string &NewTitle, const pxPoint &size)
{
	props.title = new std::string(NewTitle);
	props.size = pxPoint(size);

	props.backColor = new fColor(1, 1, 1);
	props.frontColor = new fColor(0, 0, 0);
	props.copyBackC = props.backColor;
	props.copyFrontC = props.frontColor;
}
Window_Base::~Window_Base()
{
	delete props.title;
	delete props.backColor;
	delete props.frontColor;
	delete props.copyBackC;
	delete props.copyFrontC;
}
int Window_Base::Init()
{
	std::cout << "Window class: application compiled without window interface, exiting.";
	return -1;
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
void Window_Base::DrawText(cPoint Loc, const string &text, fColor *frontColor, fColor *backColor)
{
	SetColors(frontColor, backColor);
	pxPoint px = Loc.ToPxPoint(props.size);
	pxDrawText(px, text);
	ResetColors();
}
void Window_Base::DrawLine(cPoint a, cPoint b, fColor *frontColor, fColor *backColor)
{
	SetColors(frontColor, backColor);
	pxPoint pxA = a.ToPxPoint(props.size);
	pxPoint pxB = b.ToPxPoint(props.size);
	pxDrawLine(pxA, pxB);
	ResetColors();
}
void Window_Base::DrawArrow(cPoint a, cPoint b, fColor *frontColor, fColor *backColor)
{
	fPoint t_fA = a;
	fPoint t_fB = b;

	fPoint delta = b - a;
	fPoint crossLineSingle = (delta.Normalized() * 0.01).RotateZ(3.14159 / 2);
	fPoint crossPoint1 = t_fA + (delta * 0.95) /*+ fPoint(0, 0.05);*/ +crossLineSingle;
	fPoint crossPoint2 = t_fA + (delta * 0.95) /*- fPoint(0, 0.05);*/ -crossLineSingle;

	pxPoint pxPoint1 = t_fA.ToPxPoint(props.size);
	pxPoint pxPoint2 = t_fB.ToPxPoint(props.size);
	pxPoint pxCross1 = crossPoint1.ToPxPoint(props.size);
	pxPoint pxCross2 = crossPoint2.ToPxPoint(props.size);

	SetColors(frontColor, backColor);
	pxDrawLine(pxPoint1 + *a.px, pxPoint2 + *b.px);
	pxDrawLine(pxCross1 + *a.px, pxCross2 + *b.px);/*
	pxDrawLine(pxCross1, pxPoint2);
	pxDrawLine(pxCross2, pxPoint2);*/
	ResetColors();
}
void Window_Base::DrawRect(cPoint a, cPoint b, fColor *frontColor, fColor *backColor)
{
	SetColors(frontColor, backColor);
	pxPoint pxA = a.ToPxPoint(props.size);
	pxPoint pxB = b.ToPxPoint(props.size);
	pxDrawRect(pxA, pxB);
	ResetColors();
}
// functions to be implemented
void Window_Base::Refresh() {}
void Window_Base::pxDrawText(pxPoint Loc,const string& text){}
void Window_Base::pxDrawLine(pxPoint a, pxPoint b) {}
void Window_Base::pxDrawRect(pxPoint a, pxPoint b) {}

/////////////////////////////////////////////////////////////////////////////
// private helper functions
void Window_Base::SetColors(fColor *front, fColor *back)
{
	if (front)
	{
		props.copyFrontC = props.frontColor;
		props.frontColor = front;
	}
	if (back)
	{
		props.copyBackC = props.backColor;
		props.backColor = back;
	}
}
void Window_Base::ResetColors()
{
	props.frontColor = props.copyFrontC;
	props.backColor = props.copyBackC;
}

