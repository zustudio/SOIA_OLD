
#include "CGraph.h"

using namespace SO;
using namespace SO::Drawing;

CGraph::CGraph(Window_Base* newWindow, const cPoint &newLoc, const cPoint &newSize) : CCanvas(newWindow, newLoc, newSize)
{

}

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