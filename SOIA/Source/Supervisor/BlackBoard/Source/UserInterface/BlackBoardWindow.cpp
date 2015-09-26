
#include "Definitions.h"
#include "..\..\Public\UserInterface\BlackBoardWindow.h"
using namespace Env;
using namespace Sup;

BlackBoardWindow::BlackBoardWindow()
	: ControlWindow("SOIA - BlackBoard"),
	MainLog(this, pxMargins(2, 2, 2, 44)),
	MainInput(this, pxMargins(2, -40, 2, 2), ETextBoxMode::Editable),
	Dialogue(MainInput, MainLog)
{
	
}

DialogueInterface * BlackBoardWindow::GetDialogue()
{
	return &Dialogue;
}
