
#include "Definitions.h"
#include "FreeType.h"

#include "TextObject.h"
using namespace Environment;

TextObject::TextObject(MBoundaries* InBoundaries, pxMargins InMargins, const std::string& InText)
	: GraphicsObject(InBoundaries, InMargins),
	Text(InText)
{}
