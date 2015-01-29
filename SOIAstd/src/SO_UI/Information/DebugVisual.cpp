
#include "stdafx.h"
#include "SDL.h"

#include "CTextBox.h"
#include "DebugVisual.h"


SDL_Modules_Init

using namespace SO::UI;
using namespace IA;

DebugVisual::DebugVisual(IA::Engine* NewEngine) : Window(std::string("DebugVisual"))
{
	//init vars
	CurrentEngine = NewEngine;

	//draw window
	TextMain = AddControl<CTextBox>();
	TextMain->Text = "nothing\nand less: ";
	TextMain->Text += std::to_string((int)*CurrentEngine->getDataStart()) + "\n";
	TextMain->Text += std::to_string((int)*(*CurrentEngine->getDataStart())[0]) + '\n';
	if (checkM(MText))
	{
		cIA_Data* data = (cIA_Data*)CurrentEngine->getDataStart();
		TextMain->Text += *data->Text + '\n';
	}
}
