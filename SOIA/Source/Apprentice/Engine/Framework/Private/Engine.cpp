//c Maxim Urschumzew
//Base class for different ai engines, to be inherited - provides framework for communication with Game

#include "Game.h"
#include "Engine.h"

#include <mutex>
#include <condition_variable>
#include <thread>


using namespace IA;
using namespace std;

/////////////////////////////////////////////////////////////////////////////////////////
// init
Engine::Engine(IA::Game* NewGame)
{
	CurrentGame = NewGame;
}
Engine::~Engine()
{

}

/////////////////////////////////////////////////////////////////////////////////////////
// tick
void Engine::Tick()
{
	IData* test;

	std::cout << "[IA-Engine]: no engine implementation";
}

///////////////////////////////////////////////////////////////////////////
// game io
std::vector<int>* Engine::IFuncResultOfAction(IData* Output)
{
	std::vector<int>* Result = CurrentGame->IFuncResultOfAction(Output);

	std::string logtext = "AI: " + std::to_string(int(*Output)) + "->";

	logtext += std::to_string((*Result)[0]);
	for (int i = 1; i < Result->size(); i++)
	{
		logtext += ", " + std::to_string((*Result)[i]);
	}
	//ii_Log(EDebugLevel::Info_MainFunction, logtext);

	return Result;
}
