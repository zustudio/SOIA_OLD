
#include "Definitions.h"
#include "OpenGL.h"
#include "SOIL/SOIL.h"

#include "Texture2D.h"
using namespace Environment;

Texture2D::Texture2D(unsigned char* InData, int InSizeX, int InSizeY, TextureChannels InChannels, int TexNum, TextureMode InTextureMode)
	:
	TextureNum(TexNum),
	Mode(InTextureMode),
	Channels(InChannels),
	SizeX(InSizeX),
	SizeY(InSizeY),
	Data(InData),
	UpdateRequested(true)
{}

Texture2D::Texture2D(const std::string& InFileName, int InSizeX, int InSizeY, TextureChannels InChannels, int TexNum, TextureMode InTextureMode)
	:
	TextureNum(TexNum),
	Mode(InTextureMode),
	Channels(InChannels),
	SizeX(InSizeX),
	SizeY(InSizeY),
	Data(SOIL_load_image(InFileName.c_str(), &SizeX, &SizeY, 0, int(Channels))),
	UpdateRequested(true)
{}

void Texture2D::Initialize()
{
	glGenTextures(1, &GLTexture);
	CheckGLError();

	glBindTexture(GL_TEXTURE_2D, GLTexture);
	CheckGLError();

	switch (Mode)
	{
	case Environment::TextureMode::Image:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		break;
	case Environment::TextureMode::Font:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		break;
	default:
		break;
	}
	CheckGLError();

}

void Texture2D::Update()
{
	glActiveTexture(GenerateGLTextureUnit(TextureNum));
	glBindTexture(GL_TEXTURE_2D, GLTexture);
	if (UpdateRequested)
	{
		auto GLChannels = GenerateGLChannels(Channels);
		glTexImage2D(GL_TEXTURE_2D, 0, GLChannels, SizeX, SizeY, 0, GLChannels, GL_UNSIGNED_BYTE, Data);
		CheckGLError();

		glGenerateMipmap(GL_TEXTURE_2D);
		CheckGLError();
		UpdateRequested = false;
	}
}

int Environment::Texture2D::GenerateGLChannels(TextureChannels InChannels)
{
	int result = 0;
	switch (InChannels)
	{
	case Environment::TextureChannels::None:
		break;
	case Environment::TextureChannels::R:
		result = GL_RED;
		break;
	case Environment::TextureChannels::RG:
		result = GL_RG;
		break;
	case Environment::TextureChannels::RGB:
		result = GL_RGB;
		break;
	case Environment::TextureChannels::RGBA:
		result = GL_RGBA;
		break;
	default:
		break;	
	}
	return result;
}

GLenum Environment::Texture2D::GenerateGLTextureUnit(int InTextureNum)
{
	switch (InTextureNum)
	{
	case 0:
		return GL_TEXTURE0;
	case 1:
		return GL_TEXTURE1;
	case 2:
		return GL_TEXTURE2;
	}
	return 0;
}
