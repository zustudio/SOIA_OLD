
#include "Definitions.h"

#include "CalculatorWindow.h"
using namespace Programs;
using namespace Environment;

#include "MR_Function.h"
#include "GlobalStyle.h"

CalculatorWindow::CalculatorWindow()
	: ControlWindow("Calculator", pxSize(400, 600)),
	OutputBox(this, pxMargins(5, 5, 5, 110), GlobalStyle()),
	InputBox(this, pxMargins(5, -100, 5, 5), GlobalStyle(), ETextBoxMode::Editable),
	MathCont()
{
}

void CalculatorWindow::CalculateInput()
{
	std::string input = InputBox.GetText();
	auto function = MathCont.ParseString(input);
	std::string result;

	if (function->GetValue()->GetClass() == MR_Function::StaticClass())
	{
		result = "Done.";
	}
	else
	{
		result = std::to_string(function->Execute({}));
	}

	std::string output = InputBox.GetText() + "\n                                  => " + result;
	std::string history = OutputBox.GetText();

	InputBox.SetText("");
	OutputBox.SetText(history + output + "\n\n");
}

void CalculatorWindow::Event_KeyChanged(Env::EventInfo_KeyChanged const & InInfo)
{
	if (InInfo == EventInfo_KeyChanged(GLFW_KEY_ENTER))
	{
		CalculateInput();
	}
	else
	{
		ControlWindow::Event_KeyChanged(InInfo);
	}
}
