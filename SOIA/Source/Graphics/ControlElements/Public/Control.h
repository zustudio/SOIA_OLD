/*
 * Control.h
 *
 *  Created on: Dec 6, 2014
 *      Author: mxu
 */

#pragma once

#include "cPoint.h"
#include "pxPoint.h"
#include "fPoint.h"
#include "fColor.h"
using namespace Graphics;

namespace SO
{
	class Window_Base;
}

namespace Graphics
{
	class DLLIMPEXP Control
	{
	public:
		//////////////////////////////////////////////////////
		// vars
		//---- instances ----
		SO::Window_Base* myWindow;
		//---- properties ----
		cPoint* Location;
		cPoint* Size;

		fColor* BorderColor;

		/////////////////////////////////////////////////////
		// functions
		//---- init ----
		Control(SO::Window_Base* NewWindow = nullptr, const cPoint &NewLoc = cPoint(), const cPoint &NewSize = cPoint());
		virtual ~Control();
		//---- visual ----
		void SetTrans(const fPoint &NewLoc, const fPoint &NewSize);
		void SetTrans(const cPoint &NewLoc, const cPoint &NewSize);
		//---- drawing ----
		virtual void Draw();
	};
}

