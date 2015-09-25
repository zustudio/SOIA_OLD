
#include "Definitions.h"

#include "GraphicsWindow.h"
using namespace Environment;

#include "GlobalRenderThread.h"
#include "GraphicsLayer.h"
#include "GlobalLogger.h"



#include <iostream>


//const float GraphicsWindow::vertices[] =
//{
//	-0.5f, -0.5f, 1, 0, 0,
//	0.5f, -0.5f,  0, 1, 0,
//	-0.5f, 0.5f,  0, 0, 1,
//	0.5f, 0.5f,   1, 0, 1
//};
//const GLuint GraphicsWindow::elements[] =
//{
//	0, 1, 2,
//	0, 1, 3
//};
//----- shaders
//GLchar const* GraphicsWindow::vertexShaderString =
//"#version 400\n"
//"in vec3 vertexColor;"
//"in vec2 position;"
//"out vec3 VertexColor;"
//"void main()"
//"{"
//"	VertexColor = vertexColor;"
//"	gl_Position = vec4(position,0.0,1.0);"
//"}";

//GLchar const* GraphicsWindow::fragmentShaderString =
//"#version 400\n"
//"in vec3 VertexColor;"
//"uniform vec3 extraColor;"
//"out vec4 outColor;"
//"void main()"
//"{"
//"	outColor = vec4(VertexColor, 1.0) + vec4(extraColor,1.0);"
//"}";



GraphicsWindow::GraphicsWindow(const std::string& InTitle, pxSize InSize)
	: MBoundaries(nullptr, pxMargins(0,0,0,0)),
	Size(InSize),
	Title(InTitle)
{}

void GraphicsWindow::Initialize()
{
	// get last window
	GraphicsWindow* lastWindow = GlobalRenderThread()->GetLastWindow();
	GLFWwindow* lastGLWindow = lastWindow ? lastWindow->GLWindow : nullptr;

	//----- windows creation
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	GlewContext = new GLEWContext();

	// create window
	GLWindow = glfwCreateWindow(Size.Width, Size.Height, Title.c_str(), nullptr, lastGLWindow);

	// bind events
	glfwSetFramebufferSizeCallback(GLWindow, &GraphicsWindow::StaticEvent_FramebufferResized);
	glfwSetKeyCallback(GLWindow, &GraphicsWindow::StaticEvent_KeyChanged);
	glfwSetCharCallback(GLWindow, &GraphicsWindow::StaticEvent_CharacterEntered);

	glfwMakeContextCurrent(GLWindow);
	GlobalRenderThread()->CurrentWindow = this;

	CheckGLError();

	//----- glew init
	glewExperimental = GL_TRUE;
	auto glewSuccess = glewInit();

	CheckGLError();
	
	for (auto layer : Layers)
	{
		layer->Initialize();
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

void GraphicsWindow::AddLayer(GraphicsLayer * InLayer)
{
	Layers.push_back(InLayer);
}

GraphicsWindow::~GraphicsWindow()
{

}

void GraphicsWindow::Draw()
{
	glfwMakeContextCurrent(GLWindow);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.5, 0, 0, 1);

	// start recursive update chain
	this->Update();
	for (GraphicsLayer* layer : Layers)
	{
		layer->BeginDraw();
	}
	glfwSwapBuffers(GLWindow);
}

Vector2D<pxPoint> GraphicsWindow::CalculateAbsoluteCornerLocationsOnWindow()
{
	return Vector2D<pxPoint>(pxPoint(0, 0), pxPoint(Size.Width, Size.Height));
}

void GraphicsWindow::Event_KeyChanged(EventInfo_KeyChanged const & InInfo)
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

void GraphicsWindow::StaticEvent_KeyChanged(GLFWwindow * InWindow, int InKey, int InScanCode, int InAction, int InMods)
{
	GlobalRenderThread()->GetWindowByHandle(InWindow)->Event_KeyChanged(EventInfo_KeyChanged(InKey, InScanCode, InAction, InMods));
}

void GraphicsWindow::StaticEvent_CharacterEntered(GLFWwindow * InWindow, unsigned int InChar)
{
	GlobalRenderThread()->GetWindowByHandle(InWindow)->Event_CharacterEntered(InChar);
}

