
#pragma once

#include "Texture2D.h"

namespace Environment
{
	class Font;
	class Texture2D;
	class LIBIMPEXP GlyphObject
	{
	public:
		GlyphObject();
		GlyphObject(unsigned char InChar, int InSize, Font const & InFont);
		~GlyphObject();

		static void Visualize(unsigned char* InBuffer, int InWidth, int InRows);
		static std::string CharToHexString(unsigned char InChar);

		unsigned char Char;
		std::vector<unsigned char> GlyphData;
		size_t DataSize;
		int Width;
		int Rows;
		int BitmapLeft;
		int BitmapTop;
		int AdvanceX;
		int AdvanceY;
	};
}