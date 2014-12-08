/*
 * Control.h
 *
 *  Created on: Dec 6, 2014
 *      Author: mxu
 */

#pragma once

namespace SO
{
	class Window_Base;

	namespace Drawing
	{
		class fPoint;

		class Control
		{
		public:
			//////////////////////////////////////////////////////
			// vars
			//---- instances ----
			Window_Base* myWindow;
			//---- properties ----
			fPoint* Location;
			fPoint* Size;
			/////////////////////////////////////////////////////
			// functions
			//---- init ----
			Control();
			Control(Window_Base* newWindow, const fPoint &newLoc, const fPoint &newSize);
			virtual ~Control();
			//---- drawing ----
			virtual void Draw() {}
		};
	}
}
