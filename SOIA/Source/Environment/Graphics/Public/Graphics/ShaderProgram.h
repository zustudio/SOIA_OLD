
#pragma once

#include "OpenGLForwardDefinitions.h"

#include "Shader.h"
#include "VertexBufferVariable.h"

#include <vector>
#include <string>

namespace Environment
{
	class ShaderProgram
	{
	public:
		ShaderProgram(const std::vector<Shader*>& InShaders, const std::string& InColorOutputVariable, const std::vector<VertexBufferVariable>& InInputVariables);

		void Initialize();

		void Use();

		void LinkAttributes();

	private:
		GLuint GLShaderProgram;
		std::vector<Shader*> Shaders;
		std::string ColorOutputVariable;
		std::vector<VertexBufferVariable> InputVariables;
	};
}