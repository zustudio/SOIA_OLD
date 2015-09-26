
#include "Definitions.h"
#include "OpenGL.h"

#include "ShaderProgram.h"
using namespace Environment;

ShaderProgram::ShaderProgram(const std::vector<Shader*>& InShaders, const std::string& InColorOutputVariable, const std::vector<VertexBufferVariable>& InInputVariables)
	:
	Shaders(InShaders),
	ColorOutputVariable(InColorOutputVariable),
	InputVariables(InInputVariables)
{}

void ShaderProgram::Initialize()
{
	for (Shader* shader : Shaders)
	{
		shader->Initialize();
	}
	CheckGLError();

	GLShaderProgram = glCreateProgram();
	for (Shader* shader : Shaders)
	{
		glAttachShader(GLShaderProgram, shader->GLShader);
	}
	glBindFragDataLocation(GLShaderProgram, 0, ColorOutputVariable.c_str());

	glLinkProgram(GLShaderProgram);
	glUseProgram(GLShaderProgram);

	CheckGLError();
}

void ShaderProgram::LinkAttributes()
{
	for (VertexBufferVariable var : InputVariables)
	{
		var.GLVariable = glGetAttribLocation(GLShaderProgram, var.Name.c_str());
		glVertexAttribPointer(var.GLVariable, var.Size, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * var.Buffer->GetEntrySize(), (void*)(var.Offset * sizeof(GL_FLOAT)));
		glEnableVertexAttribArray(var.GLVariable);
	}
	CheckGLError();
}

void ShaderProgram::Use()
{
	glUseProgram(GLShaderProgram);
}