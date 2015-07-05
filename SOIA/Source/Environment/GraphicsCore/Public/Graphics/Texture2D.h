
#pragma once

#include "OpenGLForwardDefinitions.h"

#include <string>

namespace Environment
{
	class LIBIMPEXP Texture2D
	{
	public:
		Texture2D(unsigned char* InData, int InSizeX, int InSizeY);
		Texture2D(const std::string& InFileName, int InSizeX, int InSizeY);

		void Initialize();

	private:
		int SizeX;
		int SizeY;
		GLuint GLTexture;
		unsigned char* Data;
	};
}