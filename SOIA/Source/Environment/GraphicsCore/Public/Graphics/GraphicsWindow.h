
#pragma once

#include <string>

//struct GLEWContext;

#define GLEW_MX
#include <GL/glew.h>
#include <GLFW/glfw3.h>

GLEWContext* glewGetContext();

namespace Environment
{
	class GraphicsLayer;
	class LIBIMPEXP GraphicsWindow
	{
		////////////////////////////////////////////////////////////////
		// Functions

		//----- ctor ------
	public:
		GraphicsWindow(float InRed);
		virtual ~GraphicsWindow();
		void Initialize(const std::string& InTitle = "No Title", int InSizeX = 500, int InSizeY = 500);

		//----- public usage -----
		void AddLayer(GraphicsLayer* InLayer);

		//----- main loop -----
		void Draw();

		//----- internal helper -----
		void CheckGLError();

		////////////////////////////////////////////////////////////////
		// Variables

		float red;

		//----- test -----
		const static float vertices[];
		const static GLuint elements[];
		//----- shaders
		static GLchar const* vertexShaderString;
		static GLchar const* fragmentShaderString;

		GLuint vertexBuffer = 0;

		GLuint vertexArrays;
		GLuint elementBuffer;
		GLuint vertexShader;
		GLuint fragmentShader;
		GLuint shaderProgram;
		GLint posAttrib;
		GLint colAttrib;
		GLint uniColor;

		//----- opengl variables -----
		GLFWwindow* GLWindow;
		GLEWContext* GlewContext;

		//----- soia variables;
		std::vector<GraphicsLayer*> Layers;
	};
}