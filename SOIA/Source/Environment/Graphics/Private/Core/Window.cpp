/*
 * Window.cpp
 *
 *  Created on: Dec 7, 2014
 *      Author: mxu
 */

#include "Definitions.h"


#include "Window.h"
#include "Control.h"		//full path needed for cl.exe vs13 compiler (includes same named file)

#include <deque>

using namespace SO;

SO::Window::Window(const std::string &NewTitle, const pxPoint &size) : Window_OS(NewTitle, size)
{

}
SO::Window::~Window()
{

}

void SO::Window::Draw()
{
	for (int n_Control = 0; n_Control < myControls.size(); n_Control++)
	{
		Control* curControl = myControls[n_Control];
		if (curControl)
			curControl->Draw();
	}
}

void SO::Window::SetControlTransformation(int ControlNum, const fPoint& InLoc, const fPoint& InSize)
{
	myControls[ControlNum]->SetTrans(InLoc, InSize);
}

void SO::Window::ForwardMouseButtonPressedEvent(const pxPoint &InCoordinates)
{
	for (auto control : myControls)
	{
		control->CheckMouseButtonPressedEventAppliance(InCoordinates);
	}
}


