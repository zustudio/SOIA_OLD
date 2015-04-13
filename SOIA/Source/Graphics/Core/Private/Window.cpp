/*
 * Window.cpp
 *
 *  Created on: Dec 7, 2014
 *      Author: mxu
 */

#include "Graphics/Core/Classes/PrivateDefinitions.h"


#include "Graphics/ControlElements/Public/Control.h"		//full path needed for cl.exe vs13 compiler (includes same named file)
#include "Graphics/Core/Public/Window.h"

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


