
#include "Definitions.h"

#include "TestWindow.h"
using namespace Environment;

#include "TextBox.h"

TestWindow::TestWindow()
	: ControlWindow("Hello_World_Window!", pxSize(1000, 200)),
	MainBox(this, pxMargins(5, 5, 5, 5))
{
	MainBox.SetText("This should be some very interesting text... ;)");
}