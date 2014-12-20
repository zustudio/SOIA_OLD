// c Maxim Urschumzew 2014

#include "stdafx.h"
#include "ConsoleService.h"
#include "Game.h"
#include "Engine.h"
#include "Window.h"
#include "CCanvas.h"
#include "CTextBox.h"

using namespace std;
using namespace SO;
//
//int threading(IA::Engine* engine)
//{
//	while (true)
//	{
//		engine->conf.AddLoops(1);
//		for (int i = 0; i < 100000; i++) { for (int j = 0; j < 1000; j++) {} }
//	}
//}

int main()
{
	std::cout << "Hallo und tschuess und wieder hallo ;)" << std::endl;

	std::cout << "win test start";
	SO::Window* win = new SO::Window();
	win->AddControl<CCanvas>();
	win->AddControl<CCanvas>();
	win->AddControl<Control>();
	CTextBox* tBox = win->AddControl<CTextBox>();
	tBox->Text = std::string("hallo, dies ist ein \nmultiline test\nbin sehr gespannt");
	//win->Start();
	thread t2 = thread(&SO::Window::Start, &*win);
	std::cout << "win test end";

	IA::Game* currentGame = new IA::Game();
	IA::Engine* currentEngine = new IA::Engine(currentGame);

	thread t1 = thread(&IA::Engine::Start, &*currentEngine);
	currentEngine->MThread.AddLoops(5);

	string text = string();
	std::getline(cin, text);

	SOIA::ConsoleService* console = new SOIA::ConsoleService(currentEngine);
	console->Start();

	win->MThread.Disable();

	t1.join();
	t2.join();
	cout << "engine exited";

	return 0;
}
