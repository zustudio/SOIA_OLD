
#pragma once

#include "MBoundaries.h"

#include "OpenGL.h"

#include "Vector2D.h"
#include "EventInfo_KeyChanged.h"

#include <string>

namespace Environment
{
	class GraphicsLayer;
}

namespace Environment
{
	enum class EWindowStatus
	{
		Closed,
		Open
	};

	class LIBIMPEXP GraphicsWindow : public MBoundaries
	{
		////////////////////////////////////////////////////////////////
		// Functions

		//----- ctor ------
	public:
		GraphicsWindow(const std::string& InTitle = "No Title", pxSize InSize = pxSize(500, 500));
		virtual ~GraphicsWindow();
		void Initialize();

		//----- management -----
		void Open();
		void Close();

		//----- public usage -----
		void AddLayer(GraphicsLayer* InLayer);

		//----- main loop -----
		virtual void Draw();

		//----- MBound functions -----
		virtual Vector2D<pxPoint> CalculateAbsoluteCornerLocationsOnWindow() override;

		//----- forwarded events -----
		virtual void Event_KeyChanged(EventInfo_KeyChanged const & InInfo);
		virtual void Event_CharacterEntered(unsigned int InChar);

		//----- static glfw events -----
		static void StaticEvent_FramebufferResized(GLFWwindow* InWindow, int InWidth, int InHeight);
		static void StaticEvent_KeyChanged(GLFWwindow* InWindow, int InKey, int InScanCode, int InAction, int InMods);
		static void StaticEvent_CharacterEntered(GLFWwindow* InWindow, unsigned int InChar);

		////////////////////////////////////////////////////////////////
		// Variables

		//----- opengl variables -----
		GLFWwindow* GLWindow;
		GLEWContext* GlewContext;

		//----- soia variables -----
		std::vector<GraphicsLayer*> Layers;
		pxSize Size;
		std::string Title;
		EWindowStatus Status;
	};
}