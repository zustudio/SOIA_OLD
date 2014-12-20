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
			Control(Window_Base* NewWindow = nullptr, const fPoint &NewLoc = fPoint(), const fPoint &NewSize = fPoint());
			virtual ~Control();
			//---- visual ----
			void SetTrans(const fPoint &NewLoc, const fPoint &NewSize);
			//---- drawing ----
			virtual void Draw() {}
		};
	}
}
