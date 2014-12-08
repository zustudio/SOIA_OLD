/*
 * Window.h
 *
 *  Created on: Dec 7, 2014
 *      Author: mxu
 */

#pragma once

#include <deque>

#include "Definitions.h"
#include "Control.h"

namespace SO
{
	class Window : public Window_OS
	{
	public:
		//////////////////////////////////////////
		// variables
		//---- instances ----
		std::deque<Control*> myControls;

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
			CClass* newControl = new CClass(static_cast<Window_Base*>(this), fPoint(0.1, 0.1), fPoint(0.8, 0.8));
			myControls.push_back((Control*)newControl);
		}
	};
}
