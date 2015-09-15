
#include "Definitions.h"

#include "CalculatorWindow.h"
using namespace Programs;
using namespace Environment;

CalculatorWindow::CalculatorWindow()
	: ControlWindow("Calculator", pxSize(500, 750)),
	OutputBox(this, pxMargins(5, 5, 5, 210)),
	InputBox(this, pxMargins(5, -200, 5, 5), ETextBoxMode::Editable)
{
}
