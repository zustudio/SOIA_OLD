

#include <iostream>

#include "GlobalRenderThread.h"
using namespace Environment;

#include "VertexBufferTemplate.h"
#include "DataUnravelerTemplate.h"
#include "GraphicsLayer.h"
#include "TextLayer.h"
#include "FreeTypeProvider.h"

#include "FileSystemProvider.h"

#include "TestWindow.h"
#include "GlobalLogger.h"

struct Point
{
	Point(float InX, float InY)
		:
		X(InX),
		Y(InY)
	{}
	float X;
	float Y;
};

struct Color
{
	Color(float InR, float InG, float InB)
		:
		R(InR),
		G(InG),
		B(InB)
	{}
	float R;
	float G;
	float B;
};


int main()
{
	/*Directory exedir = GetFileSystem()->GetExecutableDirectory();
	Path ressourcePath = exedir.GetPath().AppendFolder("Ressources");*/

	//---- test ----
	/*using PointUnraveler = DataUnravelerTemplate<Point, float, &Point::X, &Point::Y>;
	using ColorUnraveler = DataUnravelerTemplate<Color, float, &Color::R, &Color::G, &Color::B>;
	using TriUnraveler = DataUnravelerTemplate<Tri, int, &Tri::a, &Tri::b, &Tri::c>;
	Point pointA(-0.5, -0.5), pointB(0.5,-0.5), pointC(-0.5, 0.5), pointD(0.5, 0.5);
	Color colorA(1, 0, 0), colorB(0, 1, 0), colorC(0, 0, 1);
	Point coordA(0, 1), coordB(1, 1), coordC(0, 0), coordD(1,0);
	Tri triA(0, 1, 2), triB(1, 2, 3);
	
	Path imagePath = ressourcePath.AppendFolder("Images").AppendFile("SOIA-Text.png");
	auto texture = new Texture2D(imagePath.ToString(), 200, 200, ETextureChannels::RGBA);

	auto vertexBuffer = new VertexBufferTemplate<float, PointUnraveler, PointUnraveler>(VertexBufferType::Vertices, BufferContentType::Triangles);
	vertexBuffer->Add(pointA, coordA);
	vertexBuffer->Add(pointB, coordB);
	vertexBuffer->Add(pointC, coordC);
	vertexBuffer->Add(pointD, coordD);

	auto elementBuffer = new VertexBufferTemplate<int, TriUnraveler>(VertexBufferType::Elements, BufferContentType::Triangles);
	elementBuffer->Add(triA);
	elementBuffer->Add(triB);

	auto pointVar = vertexBuffer->CreateVariable(0, "position");
	auto coordVar = vertexBuffer->CreateVariable(1, "texCoords");

	auto vertexShader = new Shader(ShaderType::Vertex,
		"#version 400\n"
		"in vec2 position;"
		"in vec2 texCoords;"
		"out vec2 TexCoords;"
		"void main()"
		"{"
		"	TexCoords = texCoords;"
		"	gl_Position = vec4(position,0.0,1.0);"
		"}");

	auto fragmentShader = new Shader(ShaderType::Fragment,
		"#version 400\n"
		"in vec2 TexCoords;"
		"uniform sampler2D sampler;"
		"out vec4 outColor;"
		"void main()"
		"{"
		"	outColor = texture(sampler, TexCoords) + vec4(0, 0.1, 0, 1);"
		"}");

	auto layer = new GraphicsLayer();
	layer->Configure(
		{ vertexShader, fragmentShader },
		{ vertexBuffer, elementBuffer},
		VertexBufferType::Elements,
		{ texture },
		"outColor",
		{ pointVar, coordVar });

	Path fontPath = ressourcePath.AppendFolder("Fonts").AppendFolder("DengXian").AppendFile("DengXian.ttf");
	int size = 20;*/

	/*auto textObj = new TextObject(Vector2D<float>(-0.9, 0.5), "Artificial Intelligence Operating System");

	auto layer2 = new TextLayer(*GetFont(fontPath.ToString()), 25, { textObj });
	auto layer3 = new TextLayer(*GetFont(fontPath.ToString()), 15, { new TextObject(fPoint(-0.81,0.4), "SOIA analyses different data sets as well as itself \nand is thus able to gain insights into logic, mathematics,\nphysics, and intelligence.") });

	auto window = new GraphicsWindow({layer2, layer3});*/

	
	//GlobalLogger()->SetMinimalSeverity(Logger::Severity::DebugInfo);
	GlobalRenderThread()->Start();
	GlobalRenderThread()->AddWindow(new TestWindow());
	GlobalRenderThread()->Join();
	return 0;
}

#if def_BUILD_OS==Windows
#include <Windows.h>
extern "C"
{
	__declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
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
