
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
		virtual void Initialize();

		// Main Loop
		virtual void UpdateBuffers();
		virtual void BeginDraw();
		virtual void Draw();

		// Helper functions
		template<typename ObjectType>
		static void EraseGraphicsObjectFromBuffers(ObjectType* InObject, std::vector<ObjectType*> const & InObjectList, VertexBuffer* InVertexBuffer, VertexBuffer* InElementBuffer)
		{
			for (ObjectType* object : InObjectList)
			{
				if (object->VertexBufferRange.Lower > InObject->VertexBufferRange.Lower)
				{
					object->VertexBufferRange.MoveUp(-InObject->VertexBufferRange.Count());
				}
				if (object->ElementBufferRange.Lower > InObject->ElementBufferRange.Lower)
				{
					object->ElementBufferRange.MoveUp(-InObject->ElementBufferRange.Count());
				}
			}
			if (InVertexBuffer)
				InVertexBuffer->EraseRange(InObject->VertexBufferRange);
			if (InElementBuffer)
				InElementBuffer->EraseRange(InObject->ElementBufferRange);
		}

		////////////////////////////////////////////////////////////////
		// Variables
		ShaderProgram* Program;
		std::vector<VertexBuffer*> Buffers;
		std::vector<Texture2D*> Textures;
		GLuint VertexArrayObject;

		//------ settings ------
		VertexBufferType TargetBufferType;
	};
}