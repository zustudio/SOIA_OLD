
#include "Definitions.h"

#include "TextBox.h"
using namespace Environment;

#include "TextBoxLine.h"
#include "ControlWindow.h"


TextBox::TextBox(MBoundaries * InBoundaries, pxMargins InMargins, StyleSheet const & InStyle, ETextBoxMode InMode)
	: GraphicsControl(InBoundaries, InMargins, InStyle),
	Mode(InMode),
	Cursor(this, [this]() {return this->CalculateCursorLocation(); })
{
	AddObject(&Cursor, Layer_UnfilledGeometry);
}

//void TextBox::Update()
//{
//	if (bUpdateRequested)
//	{
//		
//
//
//
//		/*TextObjects.erase(TextObjects.begin(), TextObjects.end());
//
//		FontTexture2D* texture = ((TextLayer*)(GetLayer(Layer_Content)))->GetFontTexture();
//		std::vector<TextBoxLine> lines;
//		ContainerAwareIteratorSet<std::string> textIteratorSet = ContainerAwareIteratorSet<std::string>(Text, Text.begin());
//		while (textIteratorSet.Current != textIteratorSet.End)
//		{
//			lines.push_back(TextBoxLine(texture, GetSize().Width - 8));
//			(*--lines.end()).Fill(textIteratorSet);
//		}
//
//		int CurY = 0;
//		for (TextBoxLine& line : lines)
//		{
//			TextObjects.push_back(TextObject(this, pxMargins(4, CurY + 4, GetSize().Width - 8, -1 * texture->GetSpriteSize().Y), line.CurrentText));
//			CurY += texture->GetSpriteSize().Y + 4;
//		}
//
//		for (TextObject& object : TextObjects)
//		{
//			AddObject(&object, Layer_Content);
//		}*/
//
//		bUpdateRequested = false;
//	}
//
//	GraphicsControl::Update();
//}

std::vector<pxPoint> TextBox::CalculateCursorLocation()
{
	if (Lines.size() == 0)
		return {};

	FontTexture2D* texture = ((TextLayer*)(GetLayer(Layer_Content)))->GetFontTexture();

	Vector2D<int> cursorPosition = CursorPos_1DTo2D(Cursor.GetPosition());

	pxPoint cursorStart;
	pxPoint cursorEnd;

	TextBoxLine* selectedObject = Lines[cursorPosition.Y];

	cursorStart.Y = selectedObject->GetMargins().Top;
	cursorStart.X = selectedObject->GetMargins().Left + texture->CalculateTextWidth(std::string(selectedObject->GetText().begin(), selectedObject->GetText().begin() + cursorPosition.X));

	cursorEnd = cursorStart;
	cursorEnd.Y += texture->GetSpriteSize().Y + 4;

	return std::vector<pxPoint>({ cursorStart, cursorEnd });
}

Vector2D<int> TextBox::CursorPos_1DTo2D(int In1DPosition)
{
	Vector2D<int> out2DPosition;

	int iter_1D = 0;
	int line = 0;
	int iter_textObject = 0;
	for (iter_textObject; iter_textObject < Lines.size(); ++iter_textObject)
	{
		line = Lines[iter_textObject]->GetText().size();
		iter_1D += line;
		
		if (iter_1D >= In1DPosition)
		{
			break;
		}
	}

	out2DPosition.Y = iter_textObject;
	out2DPosition.X = line - (iter_1D - In1DPosition);

	if (iter_1D - In1DPosition == 0 && out2DPosition.Y < Lines.size() - 1)
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
		out1DPosition += Lines[i]->GetText().size();
	}

	out1DPosition += In2DPosition.X;

	return out1DPosition;
}

void TextBox::SetText(std::string const & InText)
{
	Text = InText;

	ContainerAwareIteratorSet<std::string> textIteratorSet = ContainerAwareIteratorSet<std::string>(Text, Text.begin());
	int i = 0;
	int n = Lines.size();
	for (i; i < n; ++i)
	{
		TextBoxLine* line = Lines[i];

		if (textIteratorSet.Current == textIteratorSet.End)
			break;

		line->Fill(textIteratorSet);
	}

	if (i < n) // we have too many lines
	{
		for (int j = i; j < n; ++j)
		{
			Lines[j]->SetText("");
		}
		Lines.erase(Lines.begin() + i, Lines.begin() + n - 1);
	}
	else if (textIteratorSet.Current != textIteratorSet.End) // we have too few lines
	{
		pxMargin topMargin = 2;
		if (Lines.size())
		{
			TextBoxLine* previousLine = *--Lines.end();
			pxPoint bottomLeft = previousLine->CalculateAbsoluteCornerLocationsOnWindow().Y - this->CalculateAbsoluteCornerLocationsOnWindow().X;
			topMargin = bottomLeft.Y + 3;
		}

		while (textIteratorSet.Current != textIteratorSet.End)
		{
			TextBoxLine* line = new TextBoxLine(this, topMargin, ((TextLayer*)(GetLayer(Layer_Content)))->GetFontTexture());
			Lines.push_back(line);
			line->Fill(textIteratorSet);
			AddObject(line, Layer_Content);
			topMargin = 3 + topMargin;
		}
	}


	if (Cursor.GetPosition() > Text.size())
		Cursor.SetPosition(Text.size());

	RequestUpdate();
}

std::string const & TextBox::GetText()
{
	return Text;
}

void TextBox::Event_CharacterEntered(unsigned int InChar)
{
	if (Mode != ETextBoxMode::Editable)
		return;

	int posInText = Cursor.GetPosition();
	std::string text = GetText();
	text.insert(text.begin() + posInText, InChar);
	SetText(text);
	Cursor.SetPosition(++posInText);
	RequestUpdate();
}

void TextBox::Event_KeyChanged(EventInfo_KeyChanged const & InInfo)
{
	if (Mode != ETextBoxMode::Editable)
		return;

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
			SetText(Text);
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
			SetText(Text);
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
		curPos.X = Lines[curPos.Y]->GetText().size();
		if (curPos.Y < Lines.size() - 1)
			--curPos.X;
		Cursor.SetPosition(CursorPos_2DTo1D(curPos));
		Cursor.RequestUpdate();
	}

	GraphicsControl::Event_KeyChanged(InInfo);
}

void TextBox::Event_SelectionChanged(EventInfo_SelectionChanged const & InInfo)
{
	if (Mode == ETextBoxMode::Editable)
	{
		if (InInfo == ESelectionStatus::Selected)
		{
			Cursor.SetVisibility(true);
			Space.Color = fColor(0.9, 0.9, 1);
			Space.RequestUpdate();
		}
		else
		{
			Cursor.SetVisibility(false);
			Space.Color = fColor(1, 1, 1);
			Space.RequestUpdate();
		}
	}
	else
	{
		Cursor.SetVisibility(false);
	}

	GraphicsControl::Event_SelectionChanged(InInfo);
}

void TextBox::Event_VirtualSizeChanged(pxSize const & InSize)
{
	GraphicsControl::Event_VirtualSizeChanged(InSize);

	Scroll(pxPoint(0, InSize.Height));
}
