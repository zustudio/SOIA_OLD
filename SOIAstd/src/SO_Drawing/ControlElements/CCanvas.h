/*
 * CCanvas.h
 *
 *  Created on: Dec 6, 2014
 *      Author: mxu
 */

#pragma once

#include "Control.h"

namespace SO
{
	namespace Drawing
	{
		class CCanvas : public Control
		{
		public:
			CCanvas();
			CCanvas(Window_Base* newWindow);
			CCanvas(Window_Base* newWindow, const fPoint &newLoc, const fPoint &newSize);
			virtual void Draw() override;
		};
	}
}
