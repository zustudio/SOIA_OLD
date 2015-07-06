
#include "Definitions.h"
#include "OpenGL.h"

#include "VertexBuffer.h"
using namespace Environment;
#include "RenderThread.h"


VertexBuffer::VertexBuffer(VertexBufferType InBufferType, BufferContentType InContentType)
	:
	Status(BufferStatus::AwaitingBufferUpdate),
	GLBufferType(GenerateGLBufferType(InBufferType)),
	GLContentType(GenerateGLContentType(InContentType))
{
}
void VertexBuffer::Initialize()
{
	glGenBuffers(1, &GLBuffer);
	glBindBuffer(GLBufferType, GLBuffer);
}

void VertexBuffer::RequestBufferUpdate()
{
	if (Status == BufferStatus::Idle)
	{
		Status = BufferStatus::AwaitingBufferUpdate;
	}
}

bool VertexBuffer::Update()
{
	bool success = false;

	BindBuffer();
	if (Status == BufferStatus::AwaitingBufferUpdate)
	{
		ResizeFrontBuffer();
		SwitchBuffers();
		LoadGLBuffer();

		Status = BufferStatus::Idle;
		success = true;
	}

	return success;
}


GLenum Environment::VertexBuffer::GetGLBufferType()
{
	return GLBufferType;
}

GLenum Environment::VertexBuffer::GetGLContentType()
{
	return GLContentType;
}

GLenum VertexBuffer::GenerateGLBufferType(const VertexBufferType& InBufferType)
{
	return InBufferType == VertexBufferType::Vertices ?
		GL_ARRAY_BUFFER :
		GL_ELEMENT_ARRAY_BUFFER;
}

GLenum Environment::VertexBuffer::GenerateGLContentType(const BufferContentType &InBufferContentType)
{
	return InBufferContentType == BufferContentType::Points ?
		GL_POINTS :
		InBufferContentType == BufferContentType::Lines ?
			GL_LINES :
			InBufferContentType == BufferContentType::Triangles ?
				GL_TRIANGLES :
				GL_TRIANGLE_STRIP;
}

bool VertexBuffer::IsBufferType(const VertexBufferType& InBufferType)
{
	return GLBufferType == GenerateGLBufferType(InBufferType);
}