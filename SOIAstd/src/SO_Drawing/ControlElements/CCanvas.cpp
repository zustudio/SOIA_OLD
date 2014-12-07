/*
 * CCanvas.cpp
 *
 *  Created on: Dec 6, 2014
 *      Author: mxu
 */

#include "CCanvas.h"
#include "Vector2D.h"

using namespace SO::Drawing;

///////////////////////////////////////////////////////////
// init
CCanvas::CCanvas() : Control()
{

}
CCanvas::CCanvas(Window_Base *newWindow, fPoint newLoc, fPoint newSize) : Control(newWindow, newLoc, newSize)
{

}

///////////////////////////////////////////////////////////
// draw myself
void CCanvas::Draw()
{
	myWindow->DrawRect(Location, Size);
}


