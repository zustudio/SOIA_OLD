
#include "Definitions.h"
#include "FreeType.h"

#include "GlyphObject.h"
using namespace Environment;

#include "Font.h"
#include "Texture2D.h"

GlyphObject::GlyphObject(char InChar, Font* InFont)
	:
	Char(InChar),
	Texture(nullptr, 0, 0, TextureChannels::R)
{
	FT_Load_Char(InFont->FTFace, InChar, FT_LOAD_RENDER);
	
	auto glyph = InFont->FTFace->glyph;
	Data = glyph->bitmap.buffer;
	Width = glyph->bitmap.width;
	Rows = glyph->bitmap.rows;
	BitmapLeft = glyph->bitmap_left;
	BitmapTop = glyph->bitmap_top;
	AdvanceX = glyph->advance.x;
	AdvanceY = glyph->advance.y;

	size_t DataSize = Width * Rows * sizeof(unsigned char);
	Data = new unsigned char[DataSize];
	std::memcpy(Data, glyph->bitmap.buffer, DataSize);

	Texture = Texture2D(Data, Width, Rows, TextureChannels::R, 0, TextureMode::Font);
}
GlyphObject::~GlyphObject()
{
	delete[] Data;
}