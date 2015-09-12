
#include "Definitions.h"

#include "TestWindow.h"
using namespace Environment;

#include "TextBox.h"

TestWindow::TestWindow()
	: ControlWindow("Hello_World_Window!", pxSize(1000, 200)),
	MainBox(this, pxMargins(5, 5, 5, 5))
{
	MainBox.SetText("This should be some very interesting text... ;) And here is very much of it for your information! I hope you are very pleased by this absurd mass of text which obviously doesn't fit into a line and also consists of lots of special characters, like dots. !$%&)$&(= [...]\nThere are also\n lots of extra\nlinebreaks\n\nin this sentence.");
}