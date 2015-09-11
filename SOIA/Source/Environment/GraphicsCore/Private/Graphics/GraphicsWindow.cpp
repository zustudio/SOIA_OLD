
#include "Definitions.h"

#include "GraphicsWindow.h"
using namespace Environment;

#include "RenderThreadProvider.h"
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
	GraphicsWindow* lastWindow = GetRenderThread()->GetLastWindow();
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
	glfwSetFramebufferSizeCallback(GLWindow, &GraphicsWindow::Event_FramebufferResized);

	glfwMakeContextCurrent(GLWindow);
	GetRenderThread()->CurrentWindow = this;

	CheckGLError();

	//----- glew init
	glewExperimental = GL_TRUE;
	auto glewSuccess = glewInit();

	CheckGLError();

	//////////////////////////
	// TEST CREATING
	
	for (auto layer : Layers)
	{
		layer->Initialize();
	}
	
	
	//----- element buffer
	/*glGenBuffers(1, &elementBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);*/

	//----- compile shaders
	/*vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderString, NULL);
	glCompileShader(vertexShader);

	GLint status;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
	char buffer[512];
	glGetShaderInfoLog(vertexShader, 512, NULL, buffer);


	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderString, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
	char buffer2[512];
	glGetShaderInfoLog(fragmentShader, 512, NULL, buffer2);*/

	//----- creating program out of shadersGLuint vertexArrays;
	/*shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	glBindFragDataLocation(shaderProgram, 0, "outColor");

	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);*/

	CheckGLError();
	//----- linking vertex data to shader
	/*posAttrib = glGetAttribLocation(shaderProgram, "position");
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
	glEnableVertexAttribArray(posAttrib);

	colAttrib = glGetAttribLocation(shaderProgram, "vertexColor");
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(colAttrib);*/

	//uniColor = glGetUniformLocation(shaderProgram, "extraColor");
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

void GraphicsWindow::Event_FramebufferResized(GLFWwindow * InWindow, int InWidth, int InHeight)
{
	glViewport(0, 0, InWidth, InHeight);
	GraphicsWindow* window = GetRenderThread()->GetWindowByHandle(InWindow);
	window->Size = pxSize(InWidth, InHeight);
	window->Update();
}

