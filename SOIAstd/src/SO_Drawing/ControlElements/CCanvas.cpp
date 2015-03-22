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
CCanvas::CCanvas(Window_Base *newWindow, const cPoint &newLoc, const cPoint &newSize) : Control(newWindow, newLoc, newSize)
{
	Objects = std::deque<fCanvasObject*>();
}

/////////////////////////////////////////////////////////////////////////////////
// loop
void CCanvas::Draw()
{
	Control::Draw();
	DrawRegisteredObjects();
}
void CCanvas::DrawRegisteredObjects()
{
	std::vector<fCanvasObject*> tempObjectList = std::vector<fCanvasObject*>();

	for (int iO = 0; iO < (Objects.size() + tempObjectList.size()); iO++)
	{
		int staticNum = Objects.size();
		fCanvasObject* curO = iO < staticNum ? Objects[iO] : tempObjectList[iO - staticNum];
		
		DrawSingleRegisteredObject(curO, tempObjectList);
	}
}
void CCanvas::DrawSingleRegisteredObject(fCanvasObject* InObject, std::vector<fCanvasObject*> &OutTempObjectList)
{
	switch (InObject->Type)
	{
	case CanvasObjT::Rectangle:
		myWindow->DrawRect(getAbsCP(*InObject->P1), getAbsCP(*InObject->P2, true), InObject->Color);
		break;
	case CanvasObjT::FilledRectangle:
		myWindow->DrawRect(getAbsCP(*InObject->P1), getAbsCP(*InObject->P2, true), InObject->Color, InObject->Color);
		break;
	case CanvasObjT::Line:
		myWindow->DrawLine(getAbsCP(*InObject->P1), getAbsCP(*InObject->P2), InObject->Color);
		break;
	case CanvasObjT::Arrow:
		myWindow->DrawArrow(getAbsCP(*InObject->P1), getAbsCP(*InObject->P2), InObject->Color);
		break;
	case CanvasObjT::Text:
		myWindow->DrawText(getAbsCP(*InObject->P1), *static_cast<std::string*>(InObject->Content), InObject->Color);
		break;
	case CanvasObjT::Custom:
	{
		std::vector<fCanvasObject*>* customParts = InObject->GetCustomParts();
		for (fCanvasObject* part : *customParts)
		{
			OutTempObjectList.push_back(part);
		}
	}
	break;
	}
}

/////////////////////////////////////////////////////////////////////////////////
// draw
void CCanvas::DrawRect(const fPoint &a, const fPoint &size, const fColor &color)
{
	Objects.push_back(new fCanvasObject(CanvasObjT::Rectangle, a, size, color));
}
void CCanvas::DrawFilledRect(const fPoint &a, const fPoint &size, const fColor &color)
{
	Objects.push_back(new fCanvasObject(CanvasObjT::FilledRectangle, a, size, color));
}
void CCanvas::DrawLine(const fPoint &a, const fPoint &b, const fColor &color)
{
	Objects.push_back(new fCanvasObject(CanvasObjT::Line, a, b, color));
}
void CCanvas::DrawArrow(const fPoint &a, const fPoint &b, const fColor &color)
{
	Objects.push_back(new fCanvasObject(CanvasObjT::Arrow, a, b, color));
}
void CCanvas::CDrawText(const fPoint &a, std::string *text, const fColor &color)
{
	Objects.push_back(new fCanvasObject(CanvasObjT::Text, a, a, color, text));
}
void CCanvas::DrawObject(fCanvasObject* InObject)
{
	Objects.push_back(InObject);
}
void CCanvas::HighlightObject(fCanvasObject* InObject, bool bEnable)
{
	InObject->Highlight(bEnable);
	DrawRegisteredObjects();
}
void CCanvas::Clear()
{
	fCanvasObject *first;
	while (Objects.size() > 0)
	{
		first = Objects[0];
		Objects.pop_front();
		if (first->Type != CanvasObjT::Custom)
			delete first;
	}
}
/////////////////////////////////////////////////////////////////////////////////
// calculating
cPoint CCanvas::getAbsCP(const fPoint &a, bool bDelta)
{
	cPoint back;
	back = cPoint((*Size) * a);
	back.px->X = (*Size->px).X * a.X;
	back.px->Y = (*Size->px).Y * a.Y;

	if (!bDelta)
	{
		back += *Location;
		*back.px += *Location->px;
	}

	return back;
}


