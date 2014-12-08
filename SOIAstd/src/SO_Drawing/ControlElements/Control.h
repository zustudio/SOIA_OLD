/*
 * Control.h
 *
 *  Created on: Dec 6, 2014
 *      Author: mxu
 */

#pragma once
#include "fPoint.h"
#include "Window_Base.h"

namespace SO
{
	namespace Drawing
	{
		class Control
		{
		public:
			//////////////////////////////////////////////////////
			// vars
			//---- instances ----
			Window_Base* myWindow;
			//---- properties ----
			fPoint Location;
			fPoint Size;
			/////////////////////////////////////////////////////
			// functions
			//---- init ----
			Control();
			Control(Window_Base* newWindow, fPoint newLoc, fPoint newSize);
			virtual ~Control();
			//---- drawing ----
			virtual void Draw() {}
		};
	}
}
