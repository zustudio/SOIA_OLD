
#pragma once

#include "ControlWindow.h"
#include "TextBox.h"
#include "MathContainer.h"

namespace Programs
{
	class CalculatorWindow : public Env::ControlWindow
	{
	public:
		CalculatorWindow();

		void CalculateInput();

		virtual void Event_KeyChanged(Env::EventInfo_KeyChanged const & InInfo) override;

	private:
		Env::TextBox OutputBox;
		Env::TextBox InputBox;
		MathContainer MathCont;
	};
}