
#include "Definitions.h"
#include "OpenGL.h"

#include "GraphicsLayer.h"
using namespace Environment;



GraphicsLayer::GraphicsLayer()
{}

void GraphicsLayer::Configure(const std::vector<Shader*>& InShaders, const std::vector<VertexBuffer*>& InBuffers, const VertexBufferType& InTargetBufferType, const std::vector<Texture2D*>& InTextures, const std::string& InColorOutputVariable, const std::vector<VertexBufferVariable>& InInputVariables)
{
	Buffers = InBuffers;
	TargetBufferType = InTargetBufferType;
	Textures = InTextures;
	Program = new ShaderProgram(InShaders, InColorOutputVariable, InInputVariables);
}

void GraphicsLayer::Initialize(Vector2D<int>* InSize)
{
	PixelSize = InSize;
	//----- vertex array object
	glGenVertexArrays(1, &VertexArrayObject);
	CheckGLError();

	for (auto buffer : Buffers)
	{
		buffer->Initialize();
	}
	CheckGLError();

	for (auto texture : Textures)
	{
		texture->Initialize();
	}
	CheckGLError();

	Program->Initialize();
	CheckGLError();
}

void GraphicsLayer::BeginDraw()
{
	Program->Use();

	glBindVertexArray(VertexArrayObject);

	Draw();
}
void GraphicsLayer::Draw()
{
	
	for (auto texture : Textures)
	{
		texture->Update();
	}
	
	for (auto buffer : Buffers)
	{
		if (buffer->Update())
		{
			Program->LinkAttributes();
		}
		if (buffer->IsBufferType(TargetBufferType))
		{
			auto contentType = buffer->GetGLContentType();
			switch (TargetBufferType)
			{
			case VertexBufferType::Elements:
				glDrawElements(contentType, buffer->GetRawSize() , GL_UNSIGNED_INT, 0);
				break;
			case VertexBufferType::Vertices:
				glDrawArrays(contentType, 0, buffer->GetEntryNum());
				break;
			}
			CheckGLError();
		}
	}
	
}