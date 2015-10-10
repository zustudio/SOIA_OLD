
#include "Definitions.h"

#include "GraphicsWindow.h"
using namespace Environment;

#include "GlobalRenderThread.h"
#include "GraphicsLayer.h"
#include "GlobalLogger.h"
#include "RenderTarget.h"

#include <iostream>

GraphicsWindow::GraphicsWindow(const std::string& InTitle, pxSize InSize)
	: MBoundaries(nullptr, pxMargins(0,0,0,0)),
	Size(InSize),
	Title(InTitle),
	RenderTargets(),
	FreeStencilValue(1)
{}

void GraphicsWindow::Initialize()
{
	// get last window
	GraphicsWindow* lastWindow = GlobalRenderThread()->GetLastWindow();
	GLFWwindow* lastGLWindow = lastWindow ? lastWindow->GLWindow : nullptr;

	//----- windows creation
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	GlewContext = new GLEWContext();

	// create window
	GLWindow = glfwCreateWindow(Size.Width, Size.Height, Title.c_str(), nullptr, lastGLWindow);

	// bind events
	glfwSetFramebufferSizeCallback(GLWindow, &GraphicsWindow::StaticEvent_FramebufferResized);
	glfwSetKeyCallback(GLWindow, &GraphicsWindow::StaticEvent_KeyChanged);
	glfwSetCharCallback(GLWindow, &GraphicsWindow::StaticEvent_CharacterEntered);
	glfwSetMouseButtonCallback(GLWindow, &GraphicsWindow::StaticEvent_MouseButtonChanged);
	glfwSetScrollCallback(GLWindow, &GraphicsWindow::StaticEvent_Scroll);

	glfwMakeContextCurrent(GLWindow);
	GlobalRenderThread()->CurrentWindow = this;

	CheckGLError();

	//----- glew init
	glewExperimental = GL_TRUE;
	auto glewSuccess = glewInit();

	CheckGLError();
	
	for (RenderTarget* target : RenderTargets)
	{
		target->Initialize();
	}

	CheckGLError();

	this->RequestUpdate();
}

void GraphicsWindow::Open()
{
	Status = EWindowStatus::Open;
	GlobalRenderThread()->AddWindow(this);
}

void GraphicsWindow::Close()
{
	Status = EWindowStatus::Closed;
	LOG("GraphicsWindow::Close is not implemented", Logger::Severity::Error);
}

void GraphicsWindow::AddRenderTarget(RenderTarget * InTarget)
{
	RenderTargets.push_back(InTarget);
	InTarget->SetStencilValue(NextFreeStencilValue());
}

void GraphicsWindow::RemoveRenderTarget(RenderTarget * InTarget)
{
	auto target = std::find(RenderTargets.begin(), RenderTargets.end(), InTarget);
	if (target != RenderTargets.end())
	{
		RenderTargets.erase(target);
	}
}

int GraphicsWindow::NextFreeStencilValue()
{
	int result = FreeStencilValue;
	FreeStencilValue += 1;
	return result;
}

GraphicsWindow::~GraphicsWindow()
{

}

void GraphicsWindow::Draw()
{
	glfwMakeContextCurrent(GLWindow);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glClearColor(1, 1, 1, 1);

	// start recursive update chain
	HierarchyMutex.lock();
	this->Update();
	HierarchyMutex.unlock();

	for (RenderTarget* target : RenderTargets)
	{
		target->Draw();
	}
	glfwSwapBuffers(GetWindow()->GLWindow);
}

Vector2D<pxPoint> GraphicsWindow::CalculateAbsoluteCornerLocationsOnWindow()
{
	return Vector2D<pxPoint>(pxPoint(0, 0), pxPoint(Size.Width, Size.Height));
}

std::mutex & GraphicsWindow::GetHierarchyMutex()
{
	return HierarchyMutex;
}

void GraphicsWindow::Event_KeyChanged(EventInfo_KeyChanged const & InInfo)
{

}

void GraphicsWindow::Event_MouseButtonChanged(EventInfo_MouseButtonChanged const & InInfo)
{
}

void GraphicsWindow::Event_Scroll(Vector2D<double> const & InOffset)
{
}

void GraphicsWindow::Event_CharacterEntered(unsigned int InChar)
{

}

void GraphicsWindow::StaticEvent_FramebufferResized(GLFWwindow * InWindow, int InWidth, int InHeight)
{
	LOG("Event_FramebufferResized called on window '" + Logger::ToString((void*)InWindow) + "'.", Logger::Severity::DebugInfo);
	glViewport(0, 0, InWidth, InHeight);
	GraphicsWindow* window = GlobalRenderThread()->GetWindowByHandle(InWindow);
	window->Size = pxSize(InWidth, InHeight);
	window->RequestUpdate();
	LOG("Event_FramebufferResized returned on window '" + Logger::ToString((void*)InWindow) + "'.", Logger::Severity::DebugInfo);
}

void GraphicsWindow::StaticEvent_CharacterEntered(GLFWwindow * InWindow, unsigned int InChar)
{
	GlobalRenderThread()->GetWindowByHandle(InWindow)->Event_CharacterEntered(InChar);
}

void GraphicsWindow::StaticEvent_KeyChanged(GLFWwindow * InWindow, int InKey, int InScanCode, int InAction, int InMods)
{
	GlobalRenderThread()->GetWindowByHandle(InWindow)->Event_KeyChanged(EventInfo_KeyChanged(InKey, InScanCode, InAction, InMods));
}

void GraphicsWindow::StaticEvent_MouseButtonChanged(GLFWwindow * InWindow, int InButton, int InAction, int InMods)
{
	GlobalRenderThread()->GetWindowByHandle(InWindow)->Event_MouseButtonChanged(EventInfo_MouseButtonChanged(InButton, InAction, InMods));
}

void GraphicsWindow::StaticEvent_Scroll(GLFWwindow * InWindow, double InXOffset, double InYOffset)
{
	GlobalRenderThread()->GetWindowByHandle(InWindow)->Event_Scroll(Vector2D<double>(InXOffset, InYOffset));
}

