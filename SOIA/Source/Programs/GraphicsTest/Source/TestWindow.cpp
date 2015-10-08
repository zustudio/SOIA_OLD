
#include "Definitions.h"

#include "TestWindow.h"
using namespace Environment;

#include "GlobalStyle.h"
#include "TextBox.h"

TestWindow::TestWindow()
	: ControlWindow("Hello_World_Window!", pxSize(1000, 400)),
	FirstBox(ContentArea, pxMargins(5, 5, 5, 220), GlobalStyle()),
	SecondBox(ContentArea, pxMargins(5, -100, 5, 110), GlobalStyle(), ETextBoxMode::Editable),
	ThirdBox(ContentArea, pxMargins(5, -100, 5, 5), GlobalStyle(), ETextBoxMode::Editable)
{
	FirstBox.SetText("This should be some very interesting text... ;) And here is very much of it for your information! I hope you are very pleased by this absurd mass of text which obviously doesn't fit into a line and also consists of lots of special characters, like dots. !$%&)$&(= [...]\nThere are also\n lots of extra\nlinebreaks\n\nin this sentence.");
	SecondBox.SetText("This is a second box for your pleasure... :)");
	ThirdBox.SetText("Another Text");
}