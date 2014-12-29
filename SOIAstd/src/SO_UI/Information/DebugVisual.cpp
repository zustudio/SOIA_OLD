
#include <string>

#include "IData.h"
#include "Engine.h"
#include "fPoint.h"
#include "CTextBox.h"
#include "DebugVisual.h"

using namespace SO::UI;

DebugVisual::DebugVisual(IA::Engine* NewEngine) : Window(std::string("DebugVisual"))
{
	//init vars
	CurrentEngine = NewEngine;

	//draw window
	TextMain = AddControl<CTextBox>();
	TextMain->Text = "nothing\nand less: ";
	TextMain->Text += std::to_string((int)*CurrentEngine->getDataStart()) + "\n";
	TextMain->Text += std::to_string((int)*(*CurrentEngine->getDataStart())[0]) + '\n';
	//TextMain->Text += *CurrentEngine->Knowledge->Text + '\n';
}

void DebugVisual::Start()
{
	Window::Start();
}