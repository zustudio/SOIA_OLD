
#pragma once

#include "Vector2D.h"
#include "GlyphObject.h"
#include "Font.h"

#include <string>
#include <vector>

namespace Environment
{
	class LIBIMPEXP TextObject
	{
	public:
		TextObject(/*Font* InFont, int InPixelSize, */const Vector2D<float>& InPosition, const std::string& InText);

		//void Initialize();

		//void UpdateGlyphs();

		//----- content -----
		std::string Text;
		//std::vector<GlyphObject*> Glyphs;

		//----- settings -----
		Vector2D<float> Position;
		//Font* CurrentFont;
		int PixelSize;
	};
}