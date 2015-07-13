
#include "Definitions.h"

#include "CTable.h"
using namespace Environment;
using namespace Environment;

#include <string>
#include <sstream>

CTable::CTable(Window_Base* NewWindow, const cPoint &NewLoc, const cPoint &NewSize) : Control(NewWindow, NewLoc, NewSize)
{

}

void CTable::Draw()
{
	Control::Draw();

	/// Draw the table grid.
	pxPoint dim = Matrix.Dim();
	int xMax = dim.X;
	int yMax = dim.Y;
	fPoint lineBegin;
	fPoint lineEnd;

	/// vertical lines
	for (int x = 0; x < xMax; x++)
	{
		lineBegin = fPoint(GetCellLocation(x, 0));
		lineEnd = fPoint(GetCellLocation(x, yMax));
		myWindow->DrawLine(getAbsCP(lineBegin), getAbsCP(lineEnd), new fColor(0.6, 0.6, 0.6));
	}
	/// horizontal lines
	for (int y = 0; y < yMax; y++)
	{
		lineBegin = fPoint(GetCellLocation(0, y));
		lineEnd = fPoint(GetCellLocation(xMax, y));
		myWindow->DrawLine(getAbsCP(lineBegin), getAbsCP(lineEnd), new fColor(0.4, 0.4, 0.4));
	}

	/// Draw Cells
	for (int y = 0; y < yMax; y++)
	{
		for (int x = 0; x < xMax; x++)
		{
			std::ostringstream stringStream;
			stringStream << *Matrix.get(x, y);
			std::string content = stringStream.str();

			fPoint location = GetCellLocation(x, y);

			myWindow->DrawText(getAbsCP(location), content, new fColor(0.1, 0.1, 0.1));
		}
	}

}

fPoint CTable::GetCellLocation(int X, int Y)
{
	pxPoint dimensions = Matrix.Dim();
	return fPoint(float(X) / dimensions.X, float(Y) / dimensions.Y);
}