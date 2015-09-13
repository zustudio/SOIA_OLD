
#include "Definitions.h"

#include "TextBox.h"
using namespace Environment;

#include "TextBoxLine.h"
#include "ControlWindow.h"


TextBox::TextBox(MBoundaries * InBoundaries, pxMargins InMargins, ETextBoxMode InMode)
	: GraphicsControl(InBoundaries, InMargins),
	Mode(InMode),
	Cursor(nullptr),
	LastCursorBlink(std::chrono::steady_clock::now())
{}

TextBox::~TextBox()
{
	delete Cursor;
}

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
			lines.push_back(TextBoxLine(texture, GetSize().Width - 2));
			(*--lines.end()).Fill(textIteratorSet);
		}

		int CurY = 0;
		for (TextBoxLine& line : lines)
		{
			TextObjects.push_back(TextObject(this, pxMargins(1, CurY + 1, GetSize().Width - 2, texture->GetSpriteSize().Y), line.CurrentText));
			CurY += texture->GetSpriteSize().Y + 3;
		}

		for (TextObject& object : TextObjects)
		{
			GetWindow()->CommonTextContentLayer.AddTextObject(&object);
		}

		bUpdateRequested = false;
	}


	UpdateCursor();
}

void TextBox::UpdateCursor()
{
	if (IsSelected())
	{
		FontTexture2D* texture = GetWindow()->CommonTextContentLayer.GetFontTexture();

		using namespace std::chrono;
		auto currentTime = steady_clock::now();
		auto durationSinceLastBlink = duration_cast<milliseconds>(currentTime - LastCursorBlink);

		if (durationSinceLastBlink >= 530ms)
		{
			bCursorOn = !bCursorOn;
			LastCursorBlink = steady_clock::now();

			fColor cursorColor;
			pxPoint cursorStart;
			pxPoint cursorEnd;

			cursorColor = bCursorOn ? fColor(0, 0, 0) : fColor(1, 1, 1);

			TextObject& selectedObject = TextObjects[CursorPosition.Y];

			cursorStart.Y = selectedObject.GetMargins().Top;
			cursorStart.X = selectedObject.GetMargins().Left + texture->CalculateTextWidth(std::string(selectedObject.Text.begin(), selectedObject.Text.begin() + CursorPosition.X));

			cursorEnd = cursorStart;
			cursorEnd.Y += texture->GetSpriteSize().Y;

			if (!Cursor)
			{
				Cursor = new GeometryObject(this, pxMargins(0, 0, 0, 0), cursorColor, { cursorStart, cursorEnd });
				GetWindow()->CommonUnfilledGeometryLayer.AddObject(Cursor);
			}
			else
			{
				Cursor->Edges = { cursorStart, cursorEnd };
				Cursor->Color = cursorColor;
				Cursor->RequestUpdate();
			}
		}
	}
	else
	{
		if (Cursor)
		{
			delete Cursor;
			Cursor = nullptr;
		}
	}
}

void TextBox::RequestCursorUpdate()
{
	using namespace std::chrono;
	bCursorOn = false;
	LastCursorBlink -= 10000ms;
}

void TextBox::SetText(std::string const & InText)
{
	Text = InText;
	RequestUpdate();
}

void TextBox::Event_CharacterEntered(unsigned int InChar)
{
	int posInText = GetCurserPositionInText();
	Text = Text.substr(0, posInText) + char(InChar) + Text.substr(posInText, Text.size() - posInText);
	Event_KeyChanged(EventInfo_KeyChanged(GLFW_KEY_RIGHT));
	RequestUpdate();
}

void TextBox::Event_KeyChanged(EventInfo_KeyChanged const & InInfo)
{
	auto InfoCopy = InInfo;
	if (InfoCopy.Action == (int)EKeyAction::Repeat)
		InfoCopy.Action = (int)EKeyAction::Press;

	if (InfoCopy == EventInfo_KeyChanged(GLFW_KEY_RIGHT))
	{
		if (CursorPosition.X < TextObjects[CursorPosition.Y].Text.size())
			CursorPosition.X++;
		else if (CursorPosition.Y < TextObjects.size() - 1)
		{
			CursorPosition.Y++;
			CursorPosition.X = 0;
		}
		RequestCursorUpdate();
	}
	else if (InfoCopy == EventInfo_KeyChanged(GLFW_KEY_LEFT))
	{
		if (CursorPosition.X > 0)
			CursorPosition.X--;
		else if (CursorPosition.Y > 0)
		{
			CursorPosition.Y--;
			CursorPosition.X = TextObjects[CursorPosition.Y].Text.size();
		}
		RequestCursorUpdate();
	}
	else if (InfoCopy == EventInfo_KeyChanged(GLFW_KEY_HOME) || InfoCopy == EventInfo_KeyChanged(327))
	{
		CursorPosition.X = 0;
		RequestCursorUpdate();
	}
	else if (InfoCopy == EventInfo_KeyChanged(GLFW_KEY_END) || InfoCopy == EventInfo_KeyChanged(321))
	{
		CursorPosition.X = TextObjects[CursorPosition.Y].Text.size();
		RequestCursorUpdate();
	}

	GraphicsControl::Event_KeyChanged(InInfo);
}

int TextBox::GetCurserPositionInText()
{
	int cursorPos = 0;

	for (int i = 0; i < CursorPosition.Y; i++)
	{
		cursorPos += TextObjects[i].Text.size();
	}

	cursorPos += CursorPosition.X;

	return cursorPos;
}
