/*
 * Control.cpp
 *
 *  Created on: Dec 6, 2014
 *      Author: mxu
 */

#include "Window_Base.h"
#include "fPoint.h"
#include "cPoint.h"
#include "fColor.h"
#include "Control.h"

using namespace SO;
using namespace SO::Drawing;

/////////////////////////////////////////////////////////////////////
// init
Control::Control(Window_Base* NewWindow, const fPoint &NewLoc, const fPoint &NewSize)
{
	Location = new cPoint(NewLoc, pxPoint(1, 1));
	Size = new cPoint(NewSize, pxPoint(-2, -2));
	myWindow = NewWindow;

	BorderColor = new fColor(0.5, 0.5, 0.5);
}
Control::~Control()
{

}
/////////////////////////////////////////////////////////////////////
// settings
void Control::SetTrans(const fPoint &NewLoc, const fPoint &NewSize)
{
	Location = new cPoint(NewLoc, pxPoint(1, 1));
	Size = new cPoint(NewSize, pxPoint(-2, -2));
}
/////////////////////////////////////////////////////////////////////
// draw
void Control::Draw()
{
	myWindow->DrawRect(*Location, *Size, BorderColor);
}
