
#include "Definitions.h"

#include "TextBox.h"
using namespace Environment;

#include "TextBoxLine.h"
#include "ControlWindow.h"


TextBox::TextBox(MBoundaries * InBoundaries, pxMargins InMargins, ETextBoxMode InMode)
	: GraphicsControl(InBoundaries, InMargins),
	Mode(InMode),
	Cursor(this, [this]() {return this->CalculateCursorLocation(); })
{
	GetWindow()->CommonUnfilledGeometryLayer.AddObject(&Cursor);
}

void TextBox::Update()
{
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

	GraphicsControl::Update();
}

std::vector<pxPoint> TextBox::CalculateCursorLocation()
{
	if (TextObjects.size() == 0)
		return {};

	FontTexture2D* texture = GetWindow()->CommonTextContentLayer.GetFontTexture();

	Vector2D<int> cursorPosition = CursorPos_1DTo2D(Cursor.GetPosition());

	pxPoint cursorStart;
	pxPoint cursorEnd;

	TextObject& selectedObject = TextObjects[cursorPosition.Y];

	cursorStart.Y = selectedObject.GetMargins().Top;
	cursorStart.X = selectedObject.GetMargins().Left + texture->CalculateTextWidth(std::string(selectedObject.Text.begin(), selectedObject.Text.begin() + cursorPosition.X));

	cursorEnd = cursorStart;
	cursorEnd.Y += texture->GetSpriteSize().Y;

	return std::vector<pxPoint>({ cursorStart, cursorEnd });
}

Vector2D<int> TextBox::CursorPos_1DTo2D(int In1DPosition)
{
	Vector2D<int> out2DPosition;

	int iter_1D = 0;
	int line = 0;
	int iter_textObject = 0;
	for (iter_textObject; iter_textObject < TextObjects.size(); ++iter_textObject)
	{
		line = TextObjects[iter_textObject].Text.size();
		iter_1D += line;
		
		if (iter_1D >= In1DPosition)
		{
			break;
		}
	}

	out2DPosition.Y = iter_textObject;
	out2DPosition.X = line - (iter_1D - In1DPosition);

	if (iter_1D - In1DPosition == 0 && out2DPosition.Y < TextObjects.size() - 1)
	{
		out2DPosition.Y++;
		out2DPosition.X = 0;
	}

	return out2DPosition;
}

int TextBox::CursorPos_2DTo1D(Vector2D<int> const & In2DPosition)
{
	int out1DPosition = 0;

	for (int i = 0; i < In2DPosition.Y; i++)
	{
		out1DPosition += TextObjects[i].Text.size();
	}

	out1DPosition += In2DPosition.X;

	return out1DPosition;
}

void TextBox::SetText(std::string const & InText)
{
	Text = InText;
	RequestUpdate();
}

void TextBox::Event_CharacterEntered(unsigned int InChar)
{
	int posInText = Cursor.GetPosition();
	//Text = Text.substr(0, posInText) + char(InChar) + Text.substr(posInText, Text.size() - posInText);
	Text.insert(Text.begin() + posInText, InChar);
	Cursor.SetPosition(++posInText);
	RequestUpdate();
}

void TextBox::Event_KeyChanged(EventInfo_KeyChanged const & InInfo)
{
	auto InfoCopy = InInfo;
	if (InfoCopy.Action == (int)EKeyAction::Repeat)
		InfoCopy.Action = (int)EKeyAction::Press;

	//------------------------------------------------------------
	// special characters
	if (InfoCopy == EventInfo_KeyChanged(GLFW_KEY_ENTER))
	{
		Event_CharacterEntered('\n');
	}
	else if (InfoCopy == EventInfo_KeyChanged(GLFW_KEY_BACKSPACE))
	{
		int posInText = Cursor.GetPosition();
		if (posInText > 0)
		{
			Text.erase(Text.begin() + posInText - 1);
			Cursor.SetPosition(--posInText);
			RequestUpdate();
		}
	}
	else if (InfoCopy == EventInfo_KeyChanged(GLFW_KEY_DELETE))
	{
		int posInText = Cursor.GetPosition();
		if (posInText < Text.size())
		{
			Text.erase(Text.begin() + posInText);
			RequestUpdate();
		}
	}

	//------------------------------------------------------------
	// cursor movement
	else if (InfoCopy == EventInfo_KeyChanged(GLFW_KEY_RIGHT))
	{
		int curPos = Cursor.GetPosition();
		if (curPos < Text.size())
			Cursor.SetPosition(++curPos);
		Cursor.RequestUpdate();
	}
	else if (InfoCopy == EventInfo_KeyChanged(GLFW_KEY_LEFT))
	{
		int curPos = Cursor.GetPosition();
		if (curPos > 0)
			Cursor.SetPosition(--curPos);
		Cursor.RequestUpdate();
	}
	else if (InfoCopy == EventInfo_KeyChanged(GLFW_KEY_HOME) || InfoCopy == EventInfo_KeyChanged(327))
	{
		Vector2D<int> curPos = CursorPos_1DTo2D(Cursor.GetPosition());
		curPos.X = 0;
		Cursor.SetPosition(CursorPos_2DTo1D(curPos));
		Cursor.RequestUpdate();
	}
	else if (InfoCopy == EventInfo_KeyChanged(GLFW_KEY_END) || InfoCopy == EventInfo_KeyChanged(321))
	{
		Vector2D<int> curPos = CursorPos_1DTo2D(Cursor.GetPosition());
		curPos.X = TextObjects[curPos.Y].Text.size();
		if (curPos.Y < TextObjects.size() - 1)
			--curPos.X;
		Cursor.SetPosition(CursorPos_2DTo1D(curPos));
		Cursor.RequestUpdate();
	}

	GraphicsControl::Event_KeyChanged(InInfo);
}