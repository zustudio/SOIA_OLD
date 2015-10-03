
#pragma once

#include "RenderTarget.h"

#include "GraphicsLayer.h"
#include "GeometryObject.h"
#include "EventInfo_SelectionChanged.h"
#include "EventInfo_KeyChanged.h"

namespace Environment
{
	class ControlWindow;
}

namespace Environment
{
	////////////////////////////////////////////////////////////////////
	/// \class	GraphicsControl
	/// \brief	Represents an user interactable element in a window.
	class LIBIMPEXP GraphicsControl : public RenderTarget
	{
	public:
		GraphicsControl(MBoundaries* InBoundaries, pxMargins InMargins, StyleSheet const & InStyle);

		//----- events -----
		virtual void Event_CharacterEntered(unsigned int InChar);
		virtual void Event_KeyChanged(EventInfo_KeyChanged const & InInfo);
		virtual void Event_SelectionChanged(EventInfo_SelectionChanged const & InInfo);

		//----- information -----
		bool IsSelected();


	private:
		GeometryObject Space;
		GeometryObject SelectionBorder;
		bool bSelected;
	};
}