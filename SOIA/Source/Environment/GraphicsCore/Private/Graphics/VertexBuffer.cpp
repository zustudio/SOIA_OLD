
#include "Definitions.h"
#include "OpenGL.h"

#include "VertexBuffer.h"
using namespace Environment;
#include "RenderThread.h"


VertexBuffer::VertexBuffer(VertexBufferType InBufferType)
	:
	Status(BufferStatus::AwaitingBufferUpdate),
	GLBufferType(InBufferType==VertexBufferType::Vertices?
		GL_ARRAY_BUFFER :
		GL_ELEMENT_ARRAY_BUFFER)
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

	if (Status == BufferStatus::AwaitingBufferUpdate)
	{
		BindBuffer();
		ResizeFrontBuffer();
		SwitchBuffers();
		LoadGLBuffer();

		Status = BufferStatus::Idle;
		success = true;
	}

	return success;
}

bool VertexBuffer::IsElementBuffer()
{
	return GLBufferType == GL_ELEMENT_ARRAY_BUFFER;
}