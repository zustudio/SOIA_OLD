
#pragma once

#include "GraphicsWindow.h"
#include "Thread.h"

namespace Environment
{
	class LIBIMPEXP RenderThread : public Thread
	{
	public:
		RenderThread();
		~RenderThread();

		virtual void Main() override;

		void AddWindow(GraphicsWindow* InWindow);

		GraphicsWindow* GetLastWindow();

		GraphicsWindow* CurrentWindow;

	private:
		std::vector<GraphicsWindow*> WaitingWindows;
		std::vector<GraphicsWindow*> Windows;
	};
}