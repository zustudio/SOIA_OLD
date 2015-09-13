
#pragma once

#include "OpenGLForwardDefinitions.h"

#include <string>

namespace Environment
{
	enum class ETextureMode : int
	{
		Image,
		Font
	};
	enum class ETextureChannels : int
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
		Texture2D(unsigned char* InData, int InSizeX, int InSizeY, ETextureChannels InChannels, int TexNum = 0, ETextureMode InTextureMode = ETextureMode::Image);
		Texture2D(const std::string& InFileName, int InSizeX, int InSizeY, ETextureChannels InChannels, int TexNum = 0, ETextureMode InTextureMode = ETextureMode::Image);
		Texture2D(int TexNum, ETextureMode InTextureMode, ETextureChannels InChannels);

		void Initialize();

		void Update();

	protected:
		int GenerateGLChannels(ETextureChannels InChannels);
		GLenum GenerateGLTextureUnit(int InTextureNum);

	protected:
		std::vector<unsigned char> TextureData;
		int SizeX;
		int SizeY;
		bool UpdateRequested;
	private:
		ETextureMode Mode;
		ETextureChannels Channels;
		int TextureNum;
		GLuint GLTexture;
	};
}