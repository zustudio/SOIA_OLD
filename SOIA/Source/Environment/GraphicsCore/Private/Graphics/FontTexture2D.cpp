
#include "Definitions.h"

#include "FontTexture2D.h"
using namespace Environment;

#include <assert.h>
#include <iostream>

FontTexture2D::FontTexture2D(Font const & InFont, int InFontSize)
	: Texture2D(0, ETextureMode::Font, ETextureChannels::R)
{
	// create glyphs for every character
	for (char c = 0; c < 127; ++c)
	{
		Glyphs[c] = GlyphObject(c, InFontSize, InFont);
	}

	// find biggest glyph size
	{
		Vector2D<size_t> biggestSpriteSize = Vector2D<size_t>(0, 0);
		for (GlyphObject& glyph : Glyphs)
		{
			if (glyph.Width > biggestSpriteSize.X)
				biggestSpriteSize.X = glyph.Width;
			if (glyph.Rows > biggestSpriteSize.Y)
				biggestSpriteSize.Y = glyph.Rows;
		}
		SpriteSize = biggestSpriteSize;
	}
	
	// set Texture2D fields
	SizeX = SpriteSize.X;
	SizeY = 127 * SpriteSize.Y;

	// prepare raw texture
	TextureData = std::vector<unsigned char>(SizeX * SizeY);
	std::fill(TextureData.begin(), TextureData.end(), 0x77);

	// copy glyph data to texture
	unsigned char* ptr_texture = TextureData.data();
	for (int i_glyph = 0; i_glyph < 127; ++i_glyph)
	{
		//unsigned char* ptr_debug_startTexture = ptr_texture;
		//std::cout << "###################################################" << std::endl;
		//std::cout << "# Char: " << Glyphs[i_glyph].Char << std::endl;

		GlyphObject& glyphToCopy = Glyphs[i_glyph];
		//GlyphObject::Visualize(Glyphs[i_glyph].Data.data(), Glyphs[i_glyph].Width, Glyphs[i_glyph].Rows);

		// copy rows, but skip bytes if width of glyph is not equal to biggestWidth
		unsigned char* ptr_glyphData = glyphToCopy.GlyphData.data();
		int i_row;
		for (i_row = 0; i_row < glyphToCopy.Rows; ++i_row)
		{
			std::memcpy(ptr_texture, ptr_glyphData, glyphToCopy.Width);
			ptr_texture += SpriteSize.X;
			ptr_glyphData += glyphToCopy.Width;

			//GlyphObject::Visualize(ptr_debug_startTexture, SpriteSize.X, SpriteSize.Y);
		}
		// skip remaining rows
		ptr_texture += SpriteSize.X * (SpriteSize.Y - i_row);

		// assert ptr_texture points to beginning of texture
		assert((ptr_texture - TextureData.data()) % (SpriteSize.X * SpriteSize.Y) == 0);

		//GlyphObject::Visualize(ptr_debug_startTexture, SpriteSize.X, SpriteSize.Y);
	}
}

GlyphObject& FontTexture2D::GetGlyph(char InChar)
{
	return Glyphs[InChar];
}

void FontTexture2D::GetCoordinates(char InChar, fPoint & OutLeftTop, fPoint & OutRightBottom)
{
	//float offset = float(InChar) / 127.0 * TextureData.size();
	//GlyphObject::Visualize(TextureData.data() + int(offset), SpriteSize.X, SpriteSize.Y);

	OutLeftTop = fPoint(0, float(InChar) / 127.0);
	OutRightBottom = OutLeftTop + fPoint(float(Glyphs[InChar].Width) / SizeX, float(Glyphs[InChar].Rows) / SizeY);
}

Vector2D<size_t> FontTexture2D::GetSpriteSize()
{
	return SpriteSize;
}

int FontTexture2D::CalculateTextWidth(std::string const & InText)
{
	int width = 0;
	for (char const & character : InText)
	{
		width += (Glyphs[character].AdvanceX >> 6);
	}
	return width;
}
