
#pragma once

#include "ControlWindow.h"

#include "TextBox.h"

namespace Environment
{
	class TestWindow : public ControlWindow
	{
	public:
		TestWindow();

		TextBox MainBox;
	};
}