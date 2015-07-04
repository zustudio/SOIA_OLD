
#include "Definitions.h"
#include "OpenGL.h"

#include "GraphicsLayer.h"
using namespace Environment;



GraphicsLayer::GraphicsLayer(const std::vector<Shader*>& InShaders, const std::vector<VertexBuffer*>& InBuffers, const std::string& InColorOutputVariable, const std::vector<VertexBufferVariable>& InInputVariables)
	:
	Buffers(InBuffers),
	Program(InShaders, InColorOutputVariable, InInputVariables)
{}


void GraphicsLayer::Initialize()
{
	//----- vertex array object
	glGenVertexArrays(1, &VertexArrayObject);
	CheckGLError();

	for (auto buffer : Buffers)
	{
		buffer->Initialize();
	}
	CheckGLError();

	Program.Initialize();
	CheckGLError();
}

void GraphicsLayer::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.5, 0, 0, 1);
	Program.Use();

	glBindVertexArray(VertexArrayObject);

	for (auto buffer : Buffers)
	{
		if (buffer->Update())
			Program.LinkAttributes();
		glDrawArrays(GL_TRIANGLES, 0, buffer->GetRawSize());
	}
	
	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}