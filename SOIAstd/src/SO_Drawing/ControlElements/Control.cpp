/*
 * Control.cpp
 *
 *  Created on: Dec 6, 2014
 *      Author: mxu
 */

#include "Window_Base.h"
#include "fPoint.h"
#include "cPoint.h"
#include "Control.h"

using namespace SO;
using namespace SO::Drawing;

/////////////////////////////////////////////////////////////////////
// init
Control::Control()
{
	Location = new cPoint(0,0);
	Size = new cPoint(0,0);
	myWindow = nullptr;
}
//Control::Control(const Control &oldControl)
//{
//	Location = oldControl.Location;
//	Size = oldControl.Size;
//	myWindow = oldControl.myWindow;
//}
Control::Control(Window_Base* newWindow)
{
	Location = new cPoint(fPoint(), pxPoint());
	Size = new cPoint(fPoint(0.1, 0.1), pxPoint());
	myWindow = newWindow;
}
Control::Control(Window_Base* newWindow, const fPoint &newLoc, const fPoint &newSize)
{
	fPoint fLoc = newLoc;
	fPoint fSize = newSize;
	Location = new cPoint(fLoc, pxPoint(1, 1));
	Size = new cPoint(fSize, pxPoint(-2, -2));
	myWindow = newWindow;
}
Control::~Control()
{

}
/////////////////////////////////////////////////////////////////////
// visual
void Control::SetTrans(const fPoint &newLoc, const fPoint &newSize)
{
	fPoint fLoc = newLoc;
	fPoint fSize = newSize;
	Location = new cPoint(fLoc, pxPoint(1, 1));
	Size = new cPoint(fSize, pxPoint(-2, -2));
}
