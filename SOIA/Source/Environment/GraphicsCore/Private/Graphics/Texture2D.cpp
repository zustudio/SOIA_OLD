
#include "Definitions.h"
#include "OpenGL.h"
#include "SOIL/SOIL.h"

#include "Texture2D.h"
using namespace Environment;

Texture2D::Texture2D(unsigned char* InData, int InSizeX, int InSizeY, ETextureChannels InChannels, int TexNum, ETextureMode InTextureMode)
	:
	TextureNum(TexNum),
	Mode(InTextureMode),
	Channels(InChannels),
	SizeX(InSizeX),
	SizeY(InSizeY),
	UpdateRequested(true)
{
	size_t absoluteSize = InSizeX * InSizeY * (int)InChannels;
	TextureData = std::vector<unsigned char>(absoluteSize);
	std::memcpy(TextureData.data(), InData, absoluteSize);
}

Texture2D::Texture2D(const std::string& InFileName, int InSizeX, int InSizeY, ETextureChannels InChannels, int TexNum, ETextureMode InTextureMode)
	:
	TextureNum(TexNum),
	Mode(InTextureMode),
	Channels(InChannels),
	SizeX(InSizeX),
	SizeY(InSizeY),
	UpdateRequested(true)
{
	unsigned char* data = SOIL_load_image(InFileName.c_str(), &SizeX, &SizeY, 0, int(Channels));
	size_t absoluteSize = InSizeX * InSizeY * (int)InChannels;
	TextureData = std::vector<unsigned char>(absoluteSize);
	std::memcpy(TextureData.data(), data, absoluteSize);
}

Texture2D::Texture2D(int TexNum, ETextureMode InTextureMode, ETextureChannels InChannels)
	:
	TextureNum(0),
	Mode(InTextureMode),
	Channels(InChannels),
	SizeX(0),
	SizeY(0),
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
	case Environment::ETextureMode::Image:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		break;
	case Environment::ETextureMode::Font:
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
		glTexImage2D(GL_TEXTURE_2D, 0, GLChannels, SizeX, SizeY, 0, GLChannels, GL_UNSIGNED_BYTE, TextureData.data());
		CheckGLError();

		glGenerateMipmap(GL_TEXTURE_2D);
		CheckGLError();
		UpdateRequested = false;
	}
}

int Texture2D::GenerateGLChannels(ETextureChannels InChannels)
{
	int result = 0;
	switch (InChannels)
	{
	case Environment::ETextureChannels::None:
		break;
	case Environment::ETextureChannels::R:
		result = GL_RED;
		break;
	case Environment::ETextureChannels::RG:
		result = GL_RG;
		break;
	case Environment::ETextureChannels::RGB:
		result = GL_RGB;
		break;
	case Environment::ETextureChannels::RGBA:
		result = GL_RGBA;
		break;
	default:
		break;	
	}
	return result;
}

GLenum Texture2D::GenerateGLTextureUnit(int InTextureNum)
{
	switch (InTextureNum)
	{
	case 0:
		return GL_TEXTURE0;
	case 1:
		return GL_TEXTURE1;
	case 2:
		return GL_TEXTURE2;
	case 3:
		return GL_TEXTURE3;
	}
	return 0;
}
