
#include "Definitions.h"

#include "BlackBoardWindow.h"
using namespace Env;
using namespace Sup;

#include "GlobalStyle.h"

BlackBoardWindow::BlackBoardWindow()
	: ControlWindow("SOIA - BlackBoard"),
	MainLog(ContentArea, pxMargins(2, 2, 2, 44), GlobalStyle()),
	MainInput(ContentArea, pxMargins(2, -40, 2, 2), GlobalStyle(), ETextBoxMode::Editable),
	Dialogue(MainInput, MainLog)
{
	
}

DialogueInterface * BlackBoardWindow::GetDialogue()
{
	return &Dialogue;
}
