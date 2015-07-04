
#include "Definitions.h"
#include "OpenGL.h"

#include "Shader.h"
using namespace Environment;

#include "LogProvider.h"

Shader::Shader(ShaderType InType, const std::string& InCode)
	:
	GLShaderType(InType == ShaderType::Vertex ?
		GL_VERTEX_SHADER :
		GL_FRAGMENT_SHADER),
	Code(InCode)
{}

void Shader::Initialize()
{
	auto CodeArray = Code.c_str();

	GLShader = glCreateShader(GLShaderType);
	glShaderSource(GLShader, 1, &CodeArray, NULL);
	glCompileShader(GLShader);

	GLint status;
	glGetShaderiv(GLShader, GL_COMPILE_STATUS, &status);
	char buffer[512];
	glGetShaderInfoLog(GLShader, 512, NULL, buffer);

	LOGSTATUS("Shader compiled with code: " + std::to_string(status) + " and message: " + buffer);

}