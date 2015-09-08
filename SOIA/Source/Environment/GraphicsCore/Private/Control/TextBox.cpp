
#include "Definitions.h"

#include "TextBox.h"
using namespace Environment;

#include "ControlWindow.h"

TextBox::TextBox(MBoundaries * InBoundaries, pxMargins InMargins)
	: GraphicsControl(InBoundaries, InMargins)
{}

void TextBox::SetText(std::string const & InText)
{
	GetWindow()->CommonTextContentLayer.AddTextObject(new TextObject(this, pxMargins(5, 5, 5, 5), InText));
}
