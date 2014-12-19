/*
 * CCanvas.cpp
 *
 *  Created on: Dec 6, 2014
 *      Author: mxu
 */

#include "fPoint.h"
#include "fColor.h"
#include "Vector2D.h"
#include "Window_Base.h"
#include "CCanvas.h"

using namespace SO;
using namespace SO::Drawing;

///////////////////////////////////////////////////////////
// init
CCanvas::CCanvas() : Control()
{

}
CCanvas::CCanvas(Window_Base *newWindow) : Control(newWindow)
{

}
CCanvas::CCanvas(Window_Base *newWindow, const fPoint &newLoc, const fPoint &newSize) : Control(newWindow, newLoc, newSize)
{

}

///////////////////////////////////////////////////////////
// draw myself
void CCanvas::Draw()
{
	fColor* front = new fColor(1, 0, 0);
	fColor* back = new fColor(0, 1, 0);
	myWindow->DrawRect(*Location, *Size, front, back);
}


