/*
 * Control.cpp
 *
 *  Created on: Dec 6, 2014
 *      Author: mxu
 */

#include "Window_Base.h"
#include "Control.h"

using namespace SO::Drawing;

/////////////////////////////////////////////////////////////////////
// init
Control::Control()
{
	Location = fPoint(0,0);
	Size = fPoint(0,0);
	myWindow = nullptr;
}
Control::Control(Window_Base* newWindow, fPoint newLoc, fPoint newSize)
{
	Location = newLoc;
	Size = newSize;
	myWindow = newWindow;
}
Control::~Control()
{

}

