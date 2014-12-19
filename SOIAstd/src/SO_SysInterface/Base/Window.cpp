/*
 * Window.cpp
 *
 *  Created on: Dec 7, 2014
 *      Author: mxu
 */

#include "stdafx.h"

#include <deque>

#include "../../SO_Drawing/ControlElements/Control.h"		//full path needed for cl.exe vs13 compiler (includes same named file)
#include "Window.h"

using namespace SO;
using namespace SO::Drawing;

SO::Window::Window()
{

}
SO::Window::~Window()
{

}

void SO::Window::Draw()
{
	for (int n_Control = 0; n_Control < myControls.size(); n_Control++)
	{
		myControls[n_Control]->Draw();
	}
}


