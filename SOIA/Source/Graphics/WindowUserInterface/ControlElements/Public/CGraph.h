
#pragma once

//Super class
#include "CCanvas.h"

#include "Vector2D.h"
#include "cPoint.h"
#include "fPoint.h"
#include "pxPoint.h"
#include "fColor.h"
#include "fCanvasObject.h"

#include "Window_Base.h"

namespace SO
{
	namespace Drawing
	{
		class CGraph : public CCanvas
		{
		public:
			///////////////////////////////////////////////////
			// functions
			//---- init ----
			CGraph(Window_Base* newWindow = nullptr, const cPoint &newLoc = cPoint(), const cPoint &newSize = cPoint());

			void SetDataPoints(const std::vector<fPoint> &NewDataPoints);

		private:
			std::vector<fPoint> DataPoints;

		};
	}
}