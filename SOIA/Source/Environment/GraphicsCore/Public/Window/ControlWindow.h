
#pragma once

#include "GraphicsWindow.h"

namespace Environment
{
	////////////////////////////////////////////////////////////////////
	/// \class	ControlWindow
	/// \brief	Base class for every window which uses GraphicControls.
	class ControlWindow : public GraphicsWindow
	{
	public:
		ControlWindow(std::string Name);

		void AddControl();

	private:
		
	};
}