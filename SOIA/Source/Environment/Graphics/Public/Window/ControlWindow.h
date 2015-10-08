
#pragma once

#include "GraphicsWindow.h"

#include "GraphicsControl.h"
#include "TextLayer.h"
#include "UnfilledGeometryLayer.h"
#include "FilledGeometryLayer.h"
#include "WindowArea.h"

namespace Environment
{
	////////////////////////////////////////////////////////////////////
	/// \class	ControlWindow
	/// \brief	Base class for every window which uses GraphicControls.
	class LIBIMPEXP ControlWindow : public GraphicsWindow
	{

	public:
		//----- ctor -----
		ControlWindow(std::string Name, pxSize InSize = pxSize(500, 500));

		//----- forwarded events -----
		virtual void Event_KeyChanged(EventInfo_KeyChanged const & InInfo) override;
		virtual void Event_CharacterEntered(unsigned int InChar) override;
		virtual void Event_MouseButtonChanged(EventInfo_MouseButtonChanged const & InInfo) override;
		virtual void Event_Scroll(Vector2D<double> const & InOffset) override;

	protected:
		WindowArea* ContentArea;

	private:
		void SelectNextControl(bool bForward);
		GraphicsControl* GetSelectedControl();
		std::vector<GraphicsControl*> GetControls();
		int Index_SelectedControl;
	};
}