
#pragma once

#include "ControlWindow.h"
#include "TextBox.h"

namespace Programs
{
	class CalculatorWindow : public En::ControlWindow
	{
	public:
		CalculatorWindow();

	private:
		En::TextBox OutputBox;
		En::TextBox InputBox;
	};
}