
#pragma once

#include "MBoundaries.h"

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
	class LIBIMPEXP GraphicsControl : public MBoundaries
	{
	public:
		GraphicsControl(MBoundaries* InBoundaries, pxMargins InMargins);

		//----- events -----
		virtual void Event_CharacterEntered(unsigned int InChar);
		virtual void Event_KeyChanged(EventInfo_KeyChanged const & InInfo);
		virtual void Event_SelectionChanged(EventInfo_SelectionChanged const & InInfo);

		//----- information -----
		bool IsSelected();

	protected:
		ControlWindow* GetWindow();

	private:
		GeometryObject Space;
		GeometryObject SelectionBorder;
		bool bSelected;
	};
}