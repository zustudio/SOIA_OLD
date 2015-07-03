
#include "Definitions.h"

#include "RenderThread.h"
using namespace Environment;
#include "LogProvider.h"

#define GLEW_MX
#include <GL/glew.h>
#include <GLFW/glfw3.h>

RenderThread::RenderThread()
{
}

RenderThread::~RenderThread()
{}

void RenderThread::Main()
{
	bool successfulInit = glfwInit();
	LOGSTATUS("Initializing OpenGL: " + std::to_string(successfulInit));

	int shouldClose = 0;
	while (!shouldClose)
	{
		while (WaitingWindows.size())
		{
			GraphicsWindow* window = *(WaitingWindows.begin());
			window->Initialize();
			WaitingWindows.erase(WaitingWindows.begin());
			Windows.push_back(window);
		}
		for (GraphicsWindow* window : Windows)
		{
			CurrentWindow = window;
			window->Draw();
			shouldClose += glfwWindowShouldClose(window->GLWindow);
		}
		glfwPollEvents();
	}
}

void RenderThread::AddWindow(GraphicsWindow* InWindow)
{
	WaitingWindows.push_back(InWindow);
}

GraphicsWindow* RenderThread::GetLastWindow()
{
	if (Windows.size())
		return *(Windows.end() - 1);
	else
		return nullptr;
}