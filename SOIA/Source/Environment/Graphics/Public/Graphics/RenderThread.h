
#pragma once

#include "GraphicsWindow.h"
#include "Thread.h"

#include <chrono>

namespace Environment
{
	class LIBIMPEXP RenderThread : public Thread
	{
	public:
		RenderThread();
		~RenderThread();

		virtual void Main() override;

		void AddWindow(GraphicsWindow* InWindow);

		GraphicsWindow* GetWindowByHandle(GLFWwindow* InHandle);

		GraphicsWindow* GetLastWindow();

		GraphicsWindow* CurrentWindow;

		//----- statistics -----
		float GetFPS();

	private:
		std::vector<GraphicsWindow*> WaitingWindows;
		std::vector<GraphicsWindow*> Windows;

		//----- statistics -----
		float CurrentFPS;
		int BufferSwaps;
		std::chrono::system_clock::time_point PreviousCalculation;
	};
}