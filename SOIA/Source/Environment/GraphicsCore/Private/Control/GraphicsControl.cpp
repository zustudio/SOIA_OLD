
#include "Definitions.h"

#include "GraphicsControl.h"
using namespace Environment;

#include "ControlWindow.h"

GraphicsControl::GraphicsControl(MBoundaries * InBoundaries, pxMargins InMargins)
	: MBoundaries(InBoundaries, InMargins)
{}

ControlWindow* GraphicsControl::GetWindow()
{
	return dynamic_cast<ControlWindow*>(GetTopBoundaries());
}
