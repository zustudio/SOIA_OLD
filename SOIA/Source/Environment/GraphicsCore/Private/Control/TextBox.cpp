
#include "Definitions.h"

#include "TextBox.h"
using namespace Environment;

#include "ControlWindow.h"

TextBox::TextBox(MBoundaries * InBoundaries, pxMargins InMargins)
	: GraphicsControl(InBoundaries, InMargins)
{}

void TextBox::Update()
{
	TextObjects.erase(TextObjects.begin(), TextObjects.end());

	TextObjects.push_back(TextObject(this, pxMargins(5, 5, 5, 5), Text));

	for (TextObject& object : TextObjects)
	{
		GetWindow()->CommonTextContentLayer.AddTextObject(&object);
	}

	GraphicsControl::Update();
}

void TextBox::SetText(std::string const & InText)
{
	Text = InText;
	Update();
}
