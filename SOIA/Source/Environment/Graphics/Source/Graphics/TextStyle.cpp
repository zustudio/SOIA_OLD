
#include "Definitions.h"

#include "TextStyle.h"
using namespace Environment;

TextStyle::TextStyle(Font* InFont, int InSize, fColor InColor)
	: 
	TextFont(InFont),
	Size(InSize),
	Color(InColor)
{}
