// c Maxim Urschumzew 2014

#include "stdafx.h"
#include "ConsoleService.h"

#include "SDL_GlobalVars.h"

//TEST
#include "VoidPointer.h"

using namespace SO;


int main()
{
	std::cout << "############################################\n";
	std::cout << "################## SOIAstd #################\n";
	std::cout << "# Artificial Intelligence Operating System #\n";
	std::cout << "############################################\n";

	SO::Com::ComService* ComCenter = new SO::Com::ComService();

	IA::Game_StatedState* currentGame = new IA::Game_StatedState();
	IA::Engine_SSt* currentEngine = new IA::Engine_SSt(currentGame, ComCenter);

	std::thread t1 = std::thread(&IA::Engine::Start, &*currentEngine);
	//currentEngine->MThread.AddLoops(5);


	SOIA::ConsoleService* console = new SOIA::ConsoleService(currentEngine, ComCenter);
	console->Start();

	t1.join();
	std::cout << "[SOIA]: engine exited";

	return 0;
}
