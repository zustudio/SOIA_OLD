
#include "Graphics/Core/Classes/PrivateDefinitions.h"

#include "Graphics/ControlElements/Public/CGraph.h"
using namespace SO;
using namespace Graphics;
using namespace Environment;


//////////////////////////////////////////////////////////////
// Init
CGraph::CGraph(Window_Base* newWindow, const cPoint &newLoc, const cPoint &newSize) : CCanvas(newWindow, newLoc, newSize)
{

}

//////////////////////////////////////////////////////////////
// Drawing
void CGraph::Draw()
{
	// draw border & data points
	CCanvas::Draw();

	// draw function
	fPoint Scale = fPoint(1 / (SizeMax.X - SizeMin.X), 1 / (SizeMax.Y - SizeMin.Y));
	for (GenericMathFunction function : Functions)
	{
		fPoint RelativeLocation0 = fPoint(0, 0);
		fPoint RelativeLocation1;
		for (double x = SizeMin.X; x < SizeMax.X; x += DeltaX)
		{
			RelativeLocation1 = fPoint((x - SizeMin.X) * Scale.X, 1 - (function.get(x) - SizeMin.Y) * Scale.Y);

			myWindow->DrawLine(getAbsCP(RelativeLocation0), getAbsCP(RelativeLocation1), new fColor(0.1, 0.1, 0.9));

			RelativeLocation0 = RelativeLocation1;
		}
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
	//DataPoints = NewDataPoints;

	//set properties
	float maxX = NewDataPoints[NewDataPoints.size() - 1].X;
	float maxY = NewDataPoints[NewDataPoints.size() - 1].Y;

	float scaleX = 1 / maxX;
	float scaleY = 1 / maxY;

	//draw points
	fPoint last = fPoint();
	Clear();
	for (fPoint point : NewDataPoints)
	{
		DrawLine(fPoint(0,1) + (last * fPoint(scaleX, -scaleX)), fPoint(0,1) + (point * fPoint(scaleX, -scaleX)));
		last = point;
	}
}

void CGraph::AddFunction(const GenericMathFunction &InFunctionObject)
{
	Functions.push_back(InFunctionObject);
}
