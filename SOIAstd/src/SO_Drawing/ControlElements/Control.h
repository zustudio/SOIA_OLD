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
		class fColor;

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

			fColor* BorderColor;

			/////////////////////////////////////////////////////
			// functions
			//---- init ----
			Control(Window_Base* NewWindow = nullptr, const cPoint &NewLoc = cPoint(), const cPoint &NewSize = cPoint());
			virtual ~Control();
			//---- visual ----
			void SetTrans(const fPoint &NewLoc, const fPoint &NewSize);
			//---- drawing ----
			virtual void Draw();
		};
	}
}
