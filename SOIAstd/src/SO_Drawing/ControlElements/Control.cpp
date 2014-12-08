/*
 * Control.cpp
 *
 *  Created on: Dec 6, 2014
 *      Author: mxu
 */

#include "Window_Base.h"
#include "fPoint.h"
#include "Control.h"

using namespace SO;
using namespace SO::Drawing;

/////////////////////////////////////////////////////////////////////
// init
Control::Control()
{
	Location = new fPoint(0,0);
	Size = new fPoint(0,0);
	myWindow = nullptr;
}
Control::Control(Window_Base* newWindow, const fPoint &newLoc, const fPoint &newSize)
{
	Location = new fPoint(newLoc);
	Size = new fPoint(newSize);
	myWindow = newWindow;
}
Control::~Control()
{

}

