
#include "Definitions.h"

#include "CGraph.h"
using namespace SO;
using namespace Graphics;
using namespace Environment;


//////////////////////////////////////////////////////////////
// Init
CGraph::CGraph(Window_Base* newWindow, const cPoint &newLoc, const cPoint &newSize) : Control(newWindow, newLoc, newSize)
{

}

//////////////////////////////////////////////////////////////
// Drawing
void CGraph::Draw()
{
	// draw border & data points
	Control::Draw();

	// draw function
	auto color_iter = Colors.begin();

	fPoint Scale = fPoint(1 / (SizeMax.X - SizeMin.X), 1 / (SizeMax.Y - SizeMin.Y));
	for (D1D1FunctionInterface* function : Functions)
	{
		fPoint RelativeLocation0 = fPoint(0, 0);
		fPoint RelativeLocation1;
		for (double x = SizeMin.X; x < SizeMax.X; x += DeltaX)
		{
			RelativeLocation1 = fPoint((x - SizeMin.X) * Scale.X, 1 - (function->Calculate(x) - SizeMin.Y) * Scale.Y);

			myWindow->DrawLine(getAbsCP(RelativeLocation0), getAbsCP(RelativeLocation1), &(*color_iter));

			RelativeLocation0 = RelativeLocation1;
		}
		color_iter++;
	}

	// draw data points
	fPoint RelativeLocation0 = fPoint(0, 0);
	fPoint RelativeLocation1;
	for (fPoint point : DataPoints)
	{
		RelativeLocation1 = fPoint((point.X - SizeMin.X) * Scale.X, 1 - (point.Y - SizeMin.Y) * Scale.Y);

		myWindow->DrawLine(getAbsCP(RelativeLocation0), getAbsCP(RelativeLocation1), new fColor(0.0, 0.1, 0.1));

		RelativeLocation0 = RelativeLocation1;
	}

	// draw axis
	float RelativeYAxisCoordinateX = -SizeMin.X * Scale.X;
	float RelativeXAxisCoordinateY = 1 + SizeMin.Y * Scale.Y;
	myWindow->DrawLine(getAbsCP(fPoint(RelativeYAxisCoordinateX, 0)), getAbsCP(fPoint(RelativeYAxisCoordinateX, 1)), new fColor(0.6, 0.6, 0.6));
	myWindow->DrawLine(getAbsCP(fPoint(0, RelativeXAxisCoordinateY)), getAbsCP(fPoint(1, RelativeXAxisCoordinateY)), new fColor(0.6, 0.6, 0.6));

	myWindow->DrawText(getAbsCP(fPoint(RelativeYAxisCoordinateX, 0)), std::to_string(SizeMax.Y), new fColor(0.6, 0.6, 0.6));
	myWindow->DrawText(getAbsCP(fPoint(0.9, RelativeXAxisCoordinateY - 0.1)), std::to_string(SizeMax.X), new fColor(0.6, 0.6, 0.6));
	
}

//////////////////////////////////////////////////////////////
// Data
void CGraph::SetDataPoints(const std::vector<fPoint> &NewDataPoints)
{
	DataPoints = NewDataPoints;
}

void CGraph::AddFunction(D1D1FunctionInterface *InFunctionObject, const fColor& InColor)
{
	Functions.push_back(InFunctionObject);
	Colors.push_back(InColor);
}
