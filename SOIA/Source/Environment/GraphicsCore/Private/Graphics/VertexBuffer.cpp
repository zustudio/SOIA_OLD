
#include "Definitions.h"
#include "OpenGL.h"

#include "VertexBuffer.h"
using namespace Environment;
#include "RenderThread.h"


VertexBuffer::VertexBuffer()
	:
	Status(BufferStatus::AwaitingBufferUpdate),
	FrontBuffer()
{
}
void VertexBuffer::Initialize()
{
	glGenBuffers(1, &GLBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, GLBuffer);
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
		ResizeFrontBuffer();
		SwitchBuffers();
		LoadGLBuffer();

		Status = BufferStatus::Idle;
		success = true;
	}

	return success;
}

bool VertexBuffer::ResizeFrontBuffer()
{
	FrontBuffer.resize(GetRawSize());
	return true;
}

bool VertexBuffer::LoadGLBuffer()
{
	glBindBuffer(GL_ARRAY_BUFFER, GLBuffer);
	glBufferData(GL_ARRAY_BUFFER, FrontBuffer.size() * sizeof(float), FrontBuffer.data(), GL_STATIC_DRAW);
	return true;
}

