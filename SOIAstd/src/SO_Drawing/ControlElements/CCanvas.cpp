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
}

/////////////////////////////////////////////////////////////////////////////////
// loop
void CCanvas::Draw()
{
	Control::Draw();
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
			case CanvasObjT::Text:
				myWindow->DrawText(getAbsCP(*curO.P1), *static_cast<std::string*>(curO.Content), curO.Color);
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
void CCanvas::DrawText(const fPoint &a, std::string *text, const fColor &color)
{
	Objects->push_back(new fCanvasObject(CanvasObjT::Text, a, a, color, text));
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


