
#pragma once

#include "MBoundaries.h"

#include "OpenGL.h"

#include "Vector2D.h"

#include <string>

namespace Environment
{
	class GraphicsLayer;
	class LIBIMPEXP GraphicsWindow : public MBoundaries
	{
		////////////////////////////////////////////////////////////////
		// Functions

		//----- ctor ------
	public:
		GraphicsWindow(const std::string& InTitle = "No Title", pxSize InSize = pxSize(500, 500));
		virtual ~GraphicsWindow();
		void Initialize();

		//----- public usage -----
		void AddLayer(GraphicsLayer* InLayer);

		//----- main loop -----
		virtual void Draw();

		//----- MBound functions -----
		virtual Vector2D<pxPoint> CalculateAbsoluteCornerLocationsOnWindow() override;

		//----- glfw events -----
		static void Event_FramebufferResized(GLFWwindow* InWindow, int InWidth, int InHeight);

		////////////////////////////////////////////////////////////////
		// Variables

		//----- opengl variables -----
		GLFWwindow* GLWindow;
		GLEWContext* GlewContext;

		//----- soia variables -----
		std::vector<GraphicsLayer*> Layers;
		pxSize Size;
		std::string Title;
	};
}