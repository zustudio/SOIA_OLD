/*
 * Window.h
 *
 *  Created on: Dec 7, 2014
 *      Author: mxu
 */

#pragma once

#include "Definitions.h"
#include "Control.h"

namespace SO
{
	//forward declarations
	class Window_Base;
	class Window_Win;
	class Window_Ubu;
	namespace Drawing
	{
		class Control;
	}

	class Window : public Window_OS
	{
	public:
		//////////////////////////////////////////
		// variables
		//---- instances ----
		std::deque<Drawing::Control*> myControls;

		//////////////////////////////////////////
		//functions
		//---- init ----
		Window(const std::string &NewTitle = std::string("unnamed window"), const pxPoint &size = pxPoint(400,400));
		virtual ~Window();
		//---- drawing ----
		virtual void Draw() override;
		//---- control-functions ----
		template <class CClass> void AddControl()
		{
			//create new control
			CClass* newControl = new CClass(static_cast<Window_Base*>(this));
			myControls.push_back((Drawing::Control*)newControl);

			//apply sizes
			int NumControls = myControls.size();
			fPoint cur = fPoint(0,0);
			fPoint d = fPoint(0,1/float(NumControls));

			for (int iC = 0; iC < myControls.size(); iC++)
			{
				myControls[iC]->SetTrans(cur, fPoint(1, d.Y));
				cur += d;
			}
		}
	};
}
