
#include <string>
#include <sstream>

#include "fPoint.h"
#include "Window_Base.h"
#include "CTextBox.h"

using namespace SO;
using namespace SO::Drawing;

///////////////////////////////////////////////////////////////////
// init
CTextBox::CTextBox(Window_Base *newWindow, const cPoint &newLoc, const cPoint &newSize) : Control(newWindow, newLoc, newSize)
{
	Text = std::string();
	Texts = std::deque<std::string*>();
}

///////////////////////////////////////////////////////////////////
// draw
void CTextBox::Draw()
{
	Control::Draw();

	ProcessText();

	pxPoint cur(2, 2);
	pxPoint d(0, 13);
	for (int iT = 0; iT < Texts.size(); iT++)
	{
		myWindow->DrawText(*Location + cPoint(fPoint(), cur), *Texts[iT]);
		cur += d;
	}
}

///////////////////////////////////////////////////////////////////
// text
void CTextBox::ProcessText()
{
	Texts.clear();

	int p_Last = 0;
	for (std::string::size_type p_Char = 0; p_Char < Text.size(); p_Char++)
	{
		if (Text[p_Char] == '\n')
		{
			Texts.push_back(new std::string(Text.substr(p_Last, p_Char - p_Last)));
			p_Last = p_Char + 1;
		}
	}
}
