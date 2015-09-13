
#pragma once

#include "Texture2D.h"

#include "Font.h"
#include "GlyphObject.h"
#include "fPoint.h"

#include <array>

namespace Environment
{
	//////////////////////////////////////////////////////////////////////////////
	/// \class	FontTexture2D
	/// \brief	Creates a texture from the passed font, which can be loaded into 
	///			graphics memory.
	class FontTexture2D : public Texture2D
	{
	public:
		FontTexture2D(Font const & InFont, int InFontSize);
		GlyphObject& GetGlyph(char InChar);
		void GetCoordinates(char InChar, fPoint & OutLeftTop, fPoint & OutRightBottom);
		Vector2D<size_t> GetSpriteSize();
		int CalculateTextWidth(std::string const & InText);

	private:
		Vector2D<size_t> SpriteSize;

		std::array<GlyphObject, 127> Glyphs;
	};
}