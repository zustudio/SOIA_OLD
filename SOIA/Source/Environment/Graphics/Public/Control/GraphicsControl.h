
#pragma once

#include "RenderTarget.h"

#include "GraphicsLayer.h"
#include "GeometryObject.h"
#include "ScrollBar.h"
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
		virtual void Event_VirtualSizeChanged(pxSize const & InNewSize) override;
		virtual void Event_Scroll(Vector2D<double> const & InDelta);

		//----- information -----
		bool IsSelected();


	protected:
		GeometryObject Space;
	private:
		GeometryObject SelectionBorder;
		ScrollBar VerticalScrollBar;
		bool bSelected;
	};
}