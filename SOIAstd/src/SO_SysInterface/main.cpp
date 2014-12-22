// c Maxim Urschumzew 2014

#include "stdafx.h"
#include "ConsoleService.h"
#include "Game.h"
#include "Engine.h"
#include "Engine_StatedState.h"
#include "Window.h"
#include "CCanvas.h"
#include "CTextBox.h"
#include "DebugVisual.h"

using namespace std;
using namespace SO;

int main()
{
	std::cout << "Hallo und tschuess und wieder hallo ;)" << std::endl;

	std::cout << "win test start";
	SO::Window* win = new SO::Window();
	win->AddControl<CCanvas>();
	win->AddControl<CCanvas>();
	win->AddControl<Control>();
	CTextBox* tBox = win->AddControl<CTextBox>();
	tBox->Text = std::string("hallo, dies ist ein \nmultiline test\nbin sehr gespannt\n");
	//win->Start();
	thread t2 = thread(&SO::Window::Start, &*win);
	std::cout << "win test end";

	IA::Game* currentGame = new IA::Game();
	IA::Engine_StatedState* currentEngine = new IA::Engine_StatedState(currentGame);

	thread t1 = thread(&IA::Engine::Start, &*currentEngine);
	currentEngine->MThread.AddLoops(5);

	string text = string();
	//std::getline(cin, text);

	SOIA::ConsoleService* console = new SOIA::ConsoleService(currentEngine);
	console->Start();

	win->MThread.Disable();

	t1.join();
	t2.join();
	//t3.join();
	cout << "engine exited";

	return 0;
}
