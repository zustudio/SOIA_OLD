/*
 * Control.cpp
 *
 *  Created on: Dec 6, 2014
 *      Author: mxu
 */

#include "Graphics/Core/Classes/PrivateDefinitions.h"

#include "Graphics/ControlElements/Public/Control.h"

#include "Graphics/Core/Public/Window_Base.h"


using namespace SO;

/////////////////////////////////////////////////////////////////////
// init
Control::Control(Window_Base* NewWindow, const cPoint &NewLoc, const cPoint &NewSize)
{
	Location = new cPoint(NewLoc.X, NewLoc.Y, NewLoc.px->X + 1, NewLoc.px->Y + 1);
	Size = new cPoint(NewSize.X, NewSize.Y, NewSize.px->X - 2, NewSize.px->Y - 2);
	myWindow = NewWindow;

	BorderColor = new fColor(0.5, 0.5, 0.5);
}
Control::~Control()
{

}
/////////////////////////////////////////////////////////////////////
// settings
void Control::SetTrans(const fPoint &NewLoc, const fPoint &NewSize)
{
	Location = new cPoint(NewLoc, pxPoint(1, 1));
	Size = new cPoint(NewSize, pxPoint(-2, -2));
}
void Control::SetTrans(const cPoint &NewLoc, const cPoint &NewSize)
{
	delete Location;
	delete Size;
	Location = new cPoint(NewLoc.X, NewLoc.Y, NewLoc.px->X + 1, NewLoc.px->Y + 1);
	Size = new cPoint(NewSize.X, NewSize.Y, NewSize.px->X - 2, NewSize.px->Y - 2);
}
/////////////////////////////////////////////////////////////////////
// draw
void Control::Draw()
{
	myWindow->DrawRect(*Location, *Size, BorderColor);
}

////////////////////////////////////////////////////////////////
// events
void Control::CheckMouseButtonPressedEventAppliance(const pxPoint& InCoordinates)
{
	pxPoint controlLocation = Location->ToPxPoint(myWindow->props.size);
	pxPoint controlSize = Size->ToPxPoint(myWindow->props.size);
	if (InCoordinates.X > controlLocation.X && InCoordinates.Y > controlLocation.Y)
		MouseButtonPressedEvent.Raise();
}

/////////////////////////////////////////////////////////////////////////////////
// calculating
cPoint Control::getAbsCP(const fPoint &a, bool bDelta)
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