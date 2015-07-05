
#include "Definitions.h"
#include "OpenGL.h"
#include "SOIL/SOIL.h"

#include "Texture2D.h"
using namespace Environment;

Texture2D::Texture2D(unsigned char* InData, int InSizeX, int InSizeY)
	:
	SizeX(InSizeX),
	SizeY(InSizeY),
	Data(InData)
{}

Texture2D::Texture2D(const std::string& InFileName, int InSizeX, int InSizeY)
	:
	SizeX(InSizeX),
	SizeY(InSizeY),
	Data(SOIL_load_image(InFileName.c_str(), &SizeX, &SizeY, 0, SOIL_LOAD_RGBA))
{}

void Texture2D::Initialize()
{
	glGenTextures(1, &GLTexture);
	CheckGLError();

	glBindTexture(GL_TEXTURE_2D, GLTexture);
	CheckGLError();

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, SizeX, SizeY, 0, GL_RGBA, GL_UNSIGNED_BYTE, Data);
	CheckGLError();

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	CheckGLError();

	glGenerateMipmap(GL_TEXTURE_2D);
	CheckGLError();
}