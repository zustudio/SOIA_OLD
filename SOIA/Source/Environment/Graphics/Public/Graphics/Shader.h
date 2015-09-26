
#pragma once

#include "OpenGLForwardDefinitions.h"

#include "VertexBuffer.h"
#include "VertexBufferVariable.h"

#include <string>

namespace Environment
{
	enum class ShaderType : int
	{
		Vertex,
		Fragment
	};
	class ShaderProgram;
	class LIBIMPEXP Shader
	{
		friend ShaderProgram;
	public:
		Shader(ShaderType InType, const std::string& InCode);

		void Initialize();

	private:
		GLuint GLShader;
		GLenum GLShaderType;
		std::string Code;
	};
}