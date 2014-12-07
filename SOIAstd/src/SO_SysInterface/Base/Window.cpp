/*
 * Window.cpp
 *
 *  Created on: Dec 7, 2014
 *      Author: mxu
 */

#include "Window.h"

using namespace SO;

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


