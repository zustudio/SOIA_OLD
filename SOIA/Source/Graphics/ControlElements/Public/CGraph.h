
#pragma once

//Super class
#include "Graphics/ControlElements/Public/CCanvas.h"

#include "Environment/Mathematics/DataStructures/Public/Vector2D.h"
#include "Environment/Mathematics/Functions/Public/GenericMathFunction.h"
#include "Graphics/DataStructures/Public/cPoint.h"
#include "Graphics/DataStructures/Public/fPoint.h"
#include "Graphics/DataStructures/Public/pxPoint.h"
#include "Graphics/DataStructures/Public/fColor.h"
#include "Graphics/DataStructures/Public/fCanvasObject.h"

#include "Graphics/Core/Public/Window_Base.h"

namespace Graphics
{
	class DLLIMPEXP CGraph : public CCanvas
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
		void AddFunction(const Environment::GenericMathFunction &InFunction);

		//////////////////////////////////////////////////
		// Variables
	public:
		fPoint SizeMin;
		fPoint SizeMax;
		float DeltaX;
	private:
		std::vector<fPoint> DataPoints;
		std::vector<Environment::GenericMathFunction> Functions;

	};
}
