
//include class
#include "WindowCreation.h"
using namespace UnitTest::Tests::Graphics;
using namespace Graphics;
using namespace SO;

#include "CTextbox.h"
#include "CCanvas.h"
using namespace SO::Drawing;

#include <iostream>

bool WindowCreation::Execute()
{
	Window* test = new Window();

	auto textBox1 = test->AddControl<CTextBox>();
	textBox1->Text = "Hallo, dies ist ein Test.\nUnd noch einer ;)\n";

	auto canvas1 = test->AddControl<CCanvas>();
	canvas1->DrawFilledRect(fPoint(0.2,0.1),fPoint(0.5,0.8),fColor(0.1,0.8,0.2));

	test->Open();
	return true;
}
