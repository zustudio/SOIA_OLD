
#pragma once

#include "OpenGL.h"

#include <string>

namespace Environment
{
	class GraphicsLayer;
	class LIBIMPEXP GraphicsWindow
	{
		////////////////////////////////////////////////////////////////
		// Functions

		//----- ctor ------
	public:
		GraphicsWindow(const std::vector<GraphicsLayer*>& InLayers);
		virtual ~GraphicsWindow();
		void Initialize(const std::string& InTitle = "No Title", int InSizeX = 500, int InSizeY = 500);

		//----- public usage -----
		void AddLayer(GraphicsLayer* InLayer);

		//----- main loop -----
		void Draw();

		////////////////////////////////////////////////////////////////
		// Variables

		float red;

		//----- test -----
		//const static float vertices[];
		//const static GLuint elements[];
		//----- shaders
		//static GLchar const* vertexShaderString;
		//static GLchar const* fragmentShaderString;

		/*GLuint vertexBuffer = 0;

		GLuint vertexArrays;
		GLuint elementBuffer;
		GLuint vertexShader;
		GLuint fragmentShader;
		GLuint shaderProgram;
		GLint posAttrib;
		GLint colAttrib;
		GLint uniColor;*/

		//----- opengl variables -----
		GLFWwindow* GLWindow;
		GLEWContext* GlewContext;

		//----- soia variables;
		std::vector<GraphicsLayer*> Layers;
	};
}