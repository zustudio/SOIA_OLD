
#pragma once

#include "GraphicsWindow.h"

#include "TextLayer.h"

namespace Environment
{
	////////////////////////////////////////////////////////////////////
	/// \class	ControlWindow
	/// \brief	Base class for every window which uses GraphicControls.
	class LIBIMPEXP ControlWindow : public GraphicsWindow
	{
	public:
		ControlWindow(std::string Name, pxSize InSize = pxSize(500, 500));

		TextLayer CommonTextContentLayer;
		
	};
}