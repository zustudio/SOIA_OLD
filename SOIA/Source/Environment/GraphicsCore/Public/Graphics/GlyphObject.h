
#pragma once

#include "Texture2D.h"

namespace Environment
{
	class Font;
	class Texture2D;
	class GlyphObject
	{
	public:
		GlyphObject(char InChar, Font* InFont);
		~GlyphObject();

		Texture2D Texture;

		char Char;
		unsigned char* Data;
		int Width;
		int Rows;
		int BitmapLeft;
		int BitmapTop;
		int AdvanceX;
		int AdvanceY;
	};
}