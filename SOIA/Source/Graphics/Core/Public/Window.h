/*
 * Window.h
 *
 *  Created on: Dec 7, 2014
 *      Author: mxu
 */

#pragma once

//////////////////////////////////////////////////////////////////////////////////
// os dependencies
//--- setting windows class based on running os ---
#ifdef def_BUILD_OS_Windows
	#include "Window_Win.h"
	#define Window_OS Window_Win
#elif def_OSUbuntu
	#include "Window_Ubu.h"
	#define Window_OS Window_Ubu
#else
	#include "Window_Base.h"
	#define Window_OS Window_Base
#endif

namespace Graphics
{
class Control;
}

namespace SO
{
	//forward declarations
	class Window_Base;
	class Window_Win;
	class Window_Ubu;

	class DLLIMPEXP Window : public Window_OS
	{
	public:
		//////////////////////////////////////////
		// variables
		//---- instances ----
		std::deque<Graphics::Control*> myControls;

		//////////////////////////////////////////
		//functions
		//---- init ----
		Window(const std::string &NewTitle = std::string("unnamed window"), const pxPoint &size = pxPoint(400,400));
		virtual ~Window();
		//---- drawing ----
		virtual void Draw() override;

		//---- events ----
		virtual void ForwardMouseButtonPressedEvent(const pxPoint &InCoordinates) override;

		//---- control-functions ----
		void SetControlTransformation(int ControlNum, const fPoint& InLoc, const fPoint& InSize);
		template <class CClass> CClass* AddControl()
		{
			//create new control
			CClass* newControl = new CClass(static_cast<Window_Base*>(this));
			myControls.push_back((Graphics::Control*)newControl);

			//apply sizes
			int NumControls = myControls.size();
			fPoint cur = fPoint(0,0);
			fPoint d = fPoint(0,1/float(NumControls));

			for (int iC = 0; iC < myControls.size(); iC++)
			{
				SetControlTransformation(iC, cur, fPoint(1, d.Y));
				cur += d;
			}

			return newControl;
		}
	};
}
