
#pragma once

//Super class
#include "Control.h"

#include "Vector2D.h"
#include "D1D1FunctionInterface.h"
#include "cPoint.h"
#include "fPoint.h"
#include "pxPoint.h"
#include "fColor.h"
#include "fCanvasObject.h"

#include "Window_Base.h"

namespace Graphics
{
	class LIBIMPEXP CGraph : public Control
	{
	public:
		///////////////////////////////////////////////////
		// functions
		//---- init ----
		CGraph(SO::Window_Base* newWindow = nullptr, const cPoint &newLoc = cPoint(), const cPoint &newSize = cPoint());

		//---- drawing ----
		virtual void Draw() override;

		//---- data ----
		void SetDataPoints(const std::vector<fPoint> &NewDataPoints);
		void AddFunction(Environment::D1D1FunctionInterface* InFunction, const fColor &InColor);

		//////////////////////////////////////////////////
		// Variables
	public:
		fPoint SizeMin;
		fPoint SizeMax;
		float DeltaX;
	private:
		std::vector<fPoint> DataPoints;
		std::vector<Environment::D1D1FunctionInterface*> Functions;
		std::vector<fColor> Colors;

	};
}
