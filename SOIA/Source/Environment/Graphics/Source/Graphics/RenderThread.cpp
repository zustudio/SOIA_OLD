
#include "Definitions.h"

#include "RenderThread.h"
using namespace Environment;
#include "GlobalRenderThread.h"
#include "GlobalLogger.h"

#include <thread>
#include <chrono>
using namespace std::chrono_literals;

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
			window->Draw();
			shouldClose += glfwWindowShouldClose(window->GLWindow);
		}

		BufferSwaps++;
		auto now = std::chrono::system_clock::now();
		auto duration = now - PreviousCalculation;
		if (duration >= 1s)
		{
			PreviousCalculation = now;
			CurrentFPS = float(BufferSwaps) / 1.0;
			BufferSwaps = 0;
			LOG("FPS = " + std::to_string(CurrentFPS), Logger::Severity::DebugInfo);
		}
/*
		Sleep(5ms);*/
		glfwPollEvents();
		
	}
	glfwTerminate();
}

void RenderThread::AddWindow(GraphicsWindow* InWindow)
{
	WaitingWindows.push_back(InWindow);
}

GraphicsWindow * RenderThread::GetWindowByHandle(GLFWwindow * InHandle)
{
	for (GraphicsWindow* window : Windows)
	{
		if (window->GLWindow == InHandle)
			return window;
	}
	return nullptr;
}

GraphicsWindow* RenderThread::GetLastWindow()
{
	if (Windows.size())
		return *(Windows.end() - 1);
	else
		return nullptr;
}

float RenderThread::GetFPS()
{
	return CurrentFPS;
}
