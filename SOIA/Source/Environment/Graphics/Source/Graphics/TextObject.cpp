
#include "Definitions.h"
#include "FreeType.h"

#include "TextObject.h"
using namespace Environment;

TextObject::TextObject(MBoundaries* InBoundaries, pxMargins InMargins, const std::string& InText)
	: GraphicsObject(InBoundaries, InMargins),
	Text(InText)
{}

std::string const & TextObject::GetText()
{
	return Text;
}

void TextObject::SetText(std::string InText)
{
	Text = std::move(InText);
	RequestUpdate();
}
