// c Maxim Urschumzew 2014

#include "IA_SSt.h"
#include "stdafx.h"
#include "ConsoleService.h"
#include "Game.h"
#include "Game_StatedState.h"
#include "Engine.h"
#include "Window.h"
#include "CCanvas.h"
#include "CTextBox.h"
#include "DebugVisual.h"

#include "main.h"

using namespace std;
using namespace SO;


int main()
{
	std::cout << "############################################\n";
	std::cout << "################## SOIAstd #################\n";
	std::cout << "# Artificial Intelligence Operating System #\n";
	std::cout << "############################################\n";

	IA::Game_StatedState* currentGame = new IA::Game_StatedState();
	IA::Engine_SSt* currentEngine = new IA::Engine_SSt(currentGame);

	thread t1 = thread(&IA::Engine::Start, &*currentEngine);
	currentEngine->MThread.AddLoops(5);

	SOIA::ConsoleService* console = new SOIA::ConsoleService(currentEngine);
	console->Start();

	t1.join();
	cout << "[SOIA]: engine exited";

	return 0;
}
