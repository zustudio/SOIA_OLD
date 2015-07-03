

#include <iostream>

#include "RenderThreadProvider.h"
using namespace Environment;

void main()
{
	GetRenderThread()->Start();
	GetRenderThread()->AddWindow(new GraphicsWindow(0));
	GetRenderThread()->AddWindow(new GraphicsWindow(1));
	GetRenderThread()->Join();
}

#if def_BUILD_OS==Windows
#include <Windows.h>
extern "C"
{
	_declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
}
#endif

//int main()
//{
//	////////////////////////////////////////////////////////////////////////////////
//	// Init
//	bool successfulInit = glfwInit();
//	
//	//----- windows creation
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//
//	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
//
//	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", nullptr, nullptr);	
//	glfwMakeContextCurrent(window);
//
//	CheckGLError();
//	//----- glew init
//	glewExperimental = GL_TRUE;
//	auto glewSuccess = glewInit();
//
//	CheckGLError();
//	//----- vertices
//	float vertices[] =
//	{
//		-0.5f, -0.5f, 1, 0, 0,
//		0.5f, -0.5f,  0, 1, 0,
//		-0.5f, 0.5f,  0, 0, 1,
//		0.5f, 0.5f,   1, 0, 1
//	};
//	GLuint elements[] =
//	{
//		0, 1, 2,
//		0, 1, 3
//	};
//	//----- shaders
//	GLchar const* vertexShaderString =
//		"#version 400\n"
//		"in vec3 vertexColor;"
//		"in vec2 position;"
//		"out vec3 VertexColor;"
//		"void main()"
//		"{"
//		"	VertexColor = vertexColor;"
//		"	gl_Position = vec4(position,0.0,1.0);"
//		"}";
//
//	GLchar const* fragmentShaderString =
//		"#version 400\n"
//		"in vec3 VertexColor;"
//		"out vec4 outColor;"
//		"void main()"
//		"{"
//		"	outColor = vec4(VertexColor, 1.0);"
//		"}";
//	//----- simple vertex buffer
//	GLuint vertexBuffer = 0;
//	glGenBuffers(1, &vertexBuffer);
//	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//	//----- vertex array object
//	GLuint vertexArrays;
//	glGenVertexArrays(1, &vertexArrays);
//	glBindVertexArray(vertexArrays);
//
//	//----- element buffer
//	GLuint elementBuffer;
//	glGenBuffers(1, &elementBuffer);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
//
//	//----- compile shaders
//	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
//	glShaderSource(vertexShader, 1, &vertexShaderString, NULL);
//	glCompileShader(vertexShader);
//
//	GLint status;
//	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
//	char buffer[512];
//	glGetShaderInfoLog(vertexShader, 512, NULL, buffer);
//
//	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//	glShaderSource(fragmentShader, 1, &fragmentShaderString, NULL);
//	glCompileShader(fragmentShader);
//
//	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
//	char buffer2[512];
//	glGetShaderInfoLog(fragmentShader, 512, NULL, buffer2);
//
//	//----- creating program out of shaders
//	GLuint shaderProgram = glCreateProgram();
//	glAttachShader(shaderProgram, vertexShader);
//	glAttachShader(shaderProgram, fragmentShader);
//
//	glBindFragDataLocation(shaderProgram, 0, "outColor");
//
//	glLinkProgram(shaderProgram);
//	glUseProgram(shaderProgram);
//
//	CheckGLError();
//	//----- linking vertex data to shader
//	GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
//	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), 0);
//	glEnableVertexAttribArray(posAttrib);
//
//	GLint colAttrib = glGetAttribLocation(shaderProgram, "vertexColor");
//	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
//	glEnableVertexAttribArray(colAttrib);
//
//
//	///////////////////////////////////////////////////////////////
//	// Main Loop
//	while (!glfwWindowShouldClose(window))
//	{
//		glDrawElements(GL_LINES, 6, GL_UNSIGNED_INT, 0);
//		glfwSwapBuffers(window);
//		glfwPollEvents();
//	}
//
//	glfwTerminate();
//	
//}
