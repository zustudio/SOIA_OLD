
#include "Definitions.h"
#include "FreeType.h"

#include "TextObject.h"
using namespace Environment;

//TextObject::TextObject(Font* InFont, int InPixelSize, const Vector2D<float>& InPosition, const std::string& InText)
//	:
//	CurrentFont(InFont),
//	PixelSize(InPixelSize),
//	Position(InPosition),
//	Text(InText)
//{
//	UpdateGlyphs();
//}

TextObject::TextObject(const Vector2D<float>& InPosition, const std::string & InText)
	:
	Position(InPosition),
	Text(InText)
{}

//void TextObject::Initialize()
//{
//	for (auto glyph : Glyphs)
//	{
//		glyph->TextureData.Initialize();
//		CheckGLError();
//	}
//}

//void TextObject::UpdateGlyphs()
//{
//	Glyphs.clear();
//	
//	for (char c : Text)
//	{
//		auto iter_Glyph = Find(Glyphs, c, 
//			[](GlyphObject* const& InChar) -> char
//			{
//				return InChar->Char;
//			});
//
//		if (iter_Glyph == Glyphs.end())
//			Glyphs.push_back(new GlyphObject(c, CurrentFont));
//		else
//			Glyphs.push_back(*iter_Glyph);
//	}
//}