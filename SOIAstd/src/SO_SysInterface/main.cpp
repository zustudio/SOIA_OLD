// c Maxim Urschumzew 2014

#include "stdafx.h"
#include "ConsoleService.h"
#include "Game.h"

using namespace std;

int threading()
{
	while (true)
	{
		cout << "#";
		for (int i = 0; i < 100000; i++) { for (int j = 0; j < 1000; j++) {} }
	}
}

int main()
{
	std::cout << "Hallo und tschuess und wieder hallo ;)" << std::endl;

	thread t1 = thread(threading);
	t1.detach();

	string text = string();
	std::getline(cin, text);

	t1.~thread();

	SOIA::ConsoleManager* service = new SOIA::ConsoleManager();
	


	IA::Game* currentGame = new IA::Game();
	std::cout << currentGame->IFuncResultOfAction(new IA::Data(123))->Content;

	std::getline(cin, text);

	return 0;
}
