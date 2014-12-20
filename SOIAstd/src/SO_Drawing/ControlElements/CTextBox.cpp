
#include <string>
#include <sstream>

#include "fPoint.h"
#include "Window_Base.h"
#include "CTextBox.h"

using namespace SO;
using namespace SO::Drawing;

///////////////////////////////////////////////////////////////////
// init
CTextBox::CTextBox(Window_Base *newWindow, const fPoint &newLoc, const fPoint &newSize) : Control(newWindow, newLoc, newSize)
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

	std::stringstream sstream = std::stringstream(Text);
	std::string single;

	while (std::getline(sstream, single, '\n'))
	{
		Texts.push_back(new std::string(single));
	}
}