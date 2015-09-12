
#include "Definitions.h"

#include "TextBox.h"
using namespace Environment;

#include "TextBoxLine.h"
#include "ControlWindow.h"

TextBox::TextBox(MBoundaries * InBoundaries, pxMargins InMargins)
	: GraphicsControl(InBoundaries, InMargins)
{}

void TextBox::Update()
{
	GraphicsControl::Update();

	if (bUpdateRequested)
	{
		TextObjects.erase(TextObjects.begin(), TextObjects.end());

		FontTexture2D* texture = GetWindow()->CommonTextContentLayer.GetFontTexture();
		std::vector<TextBoxLine> lines;
		ContainerAwareIteratorSet<std::string> textIteratorSet = ContainerAwareIteratorSet<std::string>(Text, Text.begin());
		while (textIteratorSet.Current != textIteratorSet.End)
		{
			lines.push_back(TextBoxLine(texture, GetSize().Width));
			(*--lines.end()).Fill(textIteratorSet);
		}

		int CurY = 0;
		for (TextBoxLine& line : lines)
		{
			TextObjects.push_back(TextObject(this, pxMargins(0, CurY, GetSize().Width, texture->GetSpriteSize().Y), line.CurrentText));
			CurY += texture->GetSpriteSize().Y + 3;
		}

		for (TextObject& object : TextObjects)
		{
			GetWindow()->CommonTextContentLayer.AddTextObject(&object);
		}

		bUpdateRequested = false;
	}
}

void TextBox::SetText(std::string const & InText)
{
	Text = InText;
	RequestUpdate();
}
