
#include "Definitions.h"
#include "FreeType.h"

#include "GlyphObject.h"
using namespace Environment;

#include "Font.h"
#include "Texture2D.h"

#include <iostream>
#include <cstring>

GlyphObject::GlyphObject()
	:
	Char(0)
{}

GlyphObject::GlyphObject(char InChar, int InSize, Font const & InFont)
	:
	Char(InChar)
{
	FT_Set_Pixel_Sizes(InFont.FTFace, 0, InSize);
	FT_Load_Char(InFont.FTFace, InChar, FT_LOAD_RENDER);
	
	auto glyph = InFont.FTFace->glyph;
	Width = glyph->bitmap.width;
	Rows = glyph->bitmap.rows;
	BitmapLeft = glyph->bitmap_left;
	BitmapTop = glyph->bitmap_top;
	AdvanceX = glyph->advance.x;
	AdvanceY = glyph->advance.y;

	DataSize = Width * Rows * sizeof(unsigned char);
	GlyphData = std::vector<unsigned char>(DataSize);
	std::memcpy(GlyphData.data(), glyph->bitmap.buffer, DataSize);

	//Visualize(GlyphData.data(), Width, Rows);
	//TextureData = Texture2D(Data, Width, Rows, ETextureChannels::R, 0, ETextureMode::Font);
}
GlyphObject::~GlyphObject()
{
}

void GlyphObject::Visualize(unsigned char * InBuffer, int InWidth, int InRows)
{
	std::cout << "-----------------------------------------" << std::endl;
	std::cout << "- Size: " << InWidth << "x" << InRows << std::endl;

	for (int i_row = 0; i_row < InRows; ++i_row)
	{
		for (int i_col = 0; i_col < InWidth; ++i_col)
		{
			unsigned char val = *InBuffer;
			//std::cout << CharToHexString(*InBuffer) << " ";
			std::cout << (val > 0x80 ? "# " : val == 0x77 ? "7 " : "  ");
			InBuffer++;
		}
		std::cout << std::endl;
	}
}

std::string GlyphObject::CharToHexString(unsigned char InChar)
{
	std::string res;
	const char hex[] = "0123456789ABCDEF";
	res += hex[InChar >> 4];
	res += hex[InChar & 0xf];

	return "0x" + res;
}
