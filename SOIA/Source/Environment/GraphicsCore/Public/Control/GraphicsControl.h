
#pragma once

#include "MBoundaries.h"

#include "GraphicsLayer.h"

namespace Environment
{
	class ControlWindow;
}

namespace Environment
{
	////////////////////////////////////////////////////////////////////
	/// \class	GraphicsControl
	/// \brief	Represents an user interactable element in a window.
	class GraphicsControl : public MBoundaries
	{
	public:
		GraphicsControl(MBoundaries* InBoundaries, pxMargins InMargins);

	protected:
		ControlWindow* GetWindow();
	};
}