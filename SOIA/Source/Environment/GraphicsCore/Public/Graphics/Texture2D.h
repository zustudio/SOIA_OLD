
#pragma once

#include "OpenGLForwardDefinitions.h"

#include <string>

namespace Environment
{
	enum class TextureMode : int
	{
		Image,
		Font
	};
	enum class TextureChannels : int
	{
		None = 0,
		R = 1,
		RG = 2,
		RGB = 3,
		RGBA = 4
	};
	class LIBIMPEXP Texture2D
	{
	public:
		Texture2D(unsigned char* InData, int InSizeX, int InSizeY, TextureChannels InChannels, int TexNum = 0, TextureMode InTextureMode = TextureMode::Image);
		Texture2D(const std::string& InFileName, int InSizeX, int InSizeY, TextureChannels InChannels, int TexNum = 0, TextureMode InTextureMode = TextureMode::Image);

		void Initialize();

		void Update();

	protected:
		int GenerateGLChannels(TextureChannels InChannels);
		GLenum GenerateGLTextureUnit(int InTextureNum);

	private:
		TextureMode Mode;
		TextureChannels Channels;
		int SizeX;
		int SizeY;
		int TextureNum;
		GLuint GLTexture;
		unsigned char* Data;
		bool UpdateRequested;
	};
}