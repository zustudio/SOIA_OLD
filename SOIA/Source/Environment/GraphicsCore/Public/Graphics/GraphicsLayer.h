
#pragma once

#include "VertexBuffer.h"
#include "ShaderProgram.h"

namespace Environment
{
	class GraphicsWindow;
	class LIBIMPEXP GraphicsLayer
	{
		friend GraphicsWindow;

		////////////////////////////////////////////////////////////////
		// Functions
	public:
		GraphicsLayer(const std::vector<Shader*>& InShaders, const std::vector<VertexBuffer*>& InBuffers,
			const std::string& InColorOutputVariable, const std::vector<VertexBufferVariable>& InInputVariables);

	protected:
		/// Compiles shaders, registers buffers, etc.
		void Initialize();

		/// Draws layer
		void Draw();

		////////////////////////////////////////////////////////////////
		// Variables
		ShaderProgram Program;
		std::vector<VertexBuffer*> Buffers;
		GLuint VertexArrayObject;
	};
}