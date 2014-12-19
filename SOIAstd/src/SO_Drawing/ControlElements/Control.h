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
		class cPoint;
		class fPoint;

		class Control
		{
		public:
			//////////////////////////////////////////////////////
			// vars
			//---- instances ----
			Window_Base* myWindow;
			//---- properties ----
			cPoint* Location;
			cPoint* Size;
			/////////////////////////////////////////////////////
			// functions
			//---- init ----
			Control();
			//Control(const Control &oldControl);
			Control(Window_Base* newWindow);
			Control(Window_Base* newWindow, const fPoint &newLoc, const fPoint &newSize);
			virtual ~Control();
			//---- visual ----
			void SetTrans(const fPoint &newLoc, const fPoint &newSize);
			//---- drawing ----
			virtual void Draw() {}
		};
	}
}
