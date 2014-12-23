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
	std::cout << "############################################\n";
	std::cout << "################## SOIAstd #################\n";
	std::cout << "# Artificial Intelligence Operating System #\n";
	std::cout << "############################################\n";

	IA::Game* currentGame = new IA::Game();
	IA::Engine_StatedState* currentEngine = new IA::Engine_StatedState(currentGame);

	thread t1 = thread(&IA::Engine::Start, &*currentEngine);
	currentEngine->MThread.AddLoops(5);

	SOIA::ConsoleService* console = new SOIA::ConsoleService(currentEngine);
	console->Start();

	t1.join();
	cout << "[SOIA]: engine exited";

	return 0;
}
