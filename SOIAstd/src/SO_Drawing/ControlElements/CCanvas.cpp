/*
 * CCanvas.cpp
 *
 *  Created on: Dec 6, 2014
 *      Author: mxu
 */

#include "fPoint.h"
#include "cPoint.h"
#include "fColor.h"
#include "Vector2D.h"
#include "fCanvasObject.h"
#include "Window_Base.h"
#include "CCanvas.h"

using namespace SO;
using namespace SO::Drawing;

///////////////////////////////////////////////////////////
// init
CCanvas::CCanvas(Window_Base *newWindow, const fPoint &newLoc, const fPoint &newSize) : Control(newWindow, newLoc, newSize)
{
	Objects = new std::deque<fCanvasObject*>();
	DrawRect(fPoint(0.4, 0.4), fPoint(0.2, 0.2), fColor(1, 0, 0));
	DrawRect(fPoint(0, 0), fPoint(0.1, 0.1), fColor(0, 1, 0));
	DrawLine(fPoint(0.5, 0.5), fPoint(0.9, 0.9), fColor(0, 0, 1));
}

/////////////////////////////////////////////////////////////////////////////////
// loop
void CCanvas::Draw()
{
	fColor* front = new fColor(0.9, 0, 0.9);
	fColor* back = new fColor(0.9, 0.9, 0.9);
	myWindow->DrawRect(*Location, *Size, front, back);

	DrawObjects();
}
void CCanvas::DrawObjects()
{
	for (int iO = 0; iO < Objects->size(); iO++)
	{
		fCanvasObject curO = (*(*Objects)[iO]);
		switch (curO.Type)
		{
			case CanvasObjT::Rectangle:
				myWindow->DrawRect(getAbsCP(*curO.P1), getAbsCP(*curO.P2, true), curO.Color);
				break;
			case CanvasObjT::Line:
				myWindow->DrawLine(getAbsCP(*curO.P1), getAbsCP(*curO.P2), curO.Color);
				break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////
// draw
void CCanvas::DrawRect(const fPoint &a, const fPoint &size, const fColor &color)
{
	Objects->push_back(new fCanvasObject(CanvasObjT::Rectangle, a, size, color));
}
void CCanvas::DrawLine(const fPoint &a, const fPoint &b, const fColor &color)
{
	Objects->push_back(new fCanvasObject(CanvasObjT::Line, a, b, color));
}
void CCanvas::Clear()
{
	fCanvasObject *first;
	while (Objects->size() > 0)
	{
		first = (*Objects)[0];
		Objects->pop_front();
		delete first;
	}
}
/////////////////////////////////////////////////////////////////////////////////
// calculating
cPoint CCanvas::getAbsCP(const fPoint &a, bool bDelta)
{
	cPoint back;
	back = cPoint((*Size) * a);
	if (!bDelta)
	{
		back += *Location;
		*back.px += *Location->px;
	}

	return back;
}


