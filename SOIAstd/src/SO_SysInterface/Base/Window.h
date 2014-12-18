/*
 * Window.h
 *
 *  Created on: Dec 7, 2014
 *      Author: mxu
 */

#pragma once

#include "Definitions.h"

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
		Window();
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
			float curX = 0;
			float curY = 0;
			float dX = 0;
			float dY = 1/(float)NumControls;

			for (int iC = 0; iC < myControls.size(); iC++)
			{
				myControls[iC]->SetTrans(fPoint(curX, curY), fPoint(1, dY));
				curY += dY;
			}
		}
	};
}
