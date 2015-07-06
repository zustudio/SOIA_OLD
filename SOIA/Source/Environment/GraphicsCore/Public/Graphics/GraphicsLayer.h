
#pragma once

#include "VertexBuffer.h"
#include "ShaderProgram.h"
#include "Texture2D.h"
#include "Vector2D.h"

namespace Environment
{
	class GraphicsWindow;
	class LIBIMPEXP GraphicsLayer
	{
		friend GraphicsWindow;

		////////////////////////////////////////////////////////////////
		// Functions
	public:
		GraphicsLayer();

		void Configure(const std::vector<Shader*>& InShaders,
			const std::vector<VertexBuffer*>& InBuffers, const VertexBufferType& InTargetBufferType, 
			const std::vector<Texture2D*>& InTextures,
			const std::string& InColorOutputVariable, const std::vector<VertexBufferVariable>& InInputVariables);

	protected:
		/// Compiles shaders, registers buffers, etc.
		virtual void Initialize(Vector2D<int>* InSize);

		/// Draws layer
		virtual void BeginDraw();
		virtual void Draw();

		////////////////////////////////////////////////////////////////
		// Variables
		ShaderProgram* Program;
		std::vector<VertexBuffer*> Buffers;
		std::vector<Texture2D*> Textures;
		GLuint VertexArrayObject;

		//------ settings ------
		VertexBufferType TargetBufferType;
		Vector2D<int>* PixelSize;
	};
}