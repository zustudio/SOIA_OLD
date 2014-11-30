// c Maxim Urschumzew 2014

#include "stdafx.h"
#include "Window_Win.h"
#include "ConsoleService.h"
#include "Game.h"
#include "Engine.h"

using namespace std;
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
	Window* win = new Window();
	thread t2 = thread(&Window::Start, &*win);
	std::cout << "win test end";

	IA::Game* currentGame = new IA::Game();
	IA::Engine* currentEngine = new IA::Engine(currentGame);

	thread t1 = thread(&IA::Engine::Start, &*currentEngine);
	currentEngine->conf.AddLoops(5);

	string text = string();
	std::getline(cin, text);

	SOIA::ConsoleService* console = new SOIA::ConsoleService(currentEngine);
	console->Start();

	t1.join();
	t2.join();
	cout << "engine exited";

	return 0;
}
