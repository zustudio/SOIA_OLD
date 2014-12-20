/*
 * CCanvas.h
 *
 *  Created on: Dec 6, 2014
 *      Author: mxu
 */

#pragma once

#include "Control.h"
#include "fColor.h"

namespace SO
{
	namespace Drawing
	{
		class fPoint;
		class fColor;
		class fCanvasObject;

		class CCanvas : public Control
		{
		public:
			/////////////////////////////////////////////////////////////////////////////////////
			// variables
			//---- draw ----
			std::deque<fCanvasObject*>* Objects;

			/////////////////////////////////////////////////////////////////////////////////////
			// functions
			//---- init ----
			CCanvas();
			CCanvas(Window_Base* newWindow);
			CCanvas(Window_Base* newWindow, const fPoint &newLoc, const fPoint &newSize);
			//---- loop ----
			virtual void Draw() override;
			void DrawObjects();
			//---- draw ----
			void DrawRect(const fPoint &a, const fPoint &size, const fColor &color = fColor(0, 0, 0));
			void DrawLine(const fPoint &a, const fPoint &b, const fColor &color = fColor(0, 0, 0));
			void Clear();
			//---- calc ----
		private:
			cPoint getAbsCP(const fPoint &a, bool bDelta = false);
		};
	}
}
