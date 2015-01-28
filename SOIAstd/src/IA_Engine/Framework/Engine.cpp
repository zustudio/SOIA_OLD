//c Maxim Urschumzew
//Base class for different ai engines, to be inherited - provides framework for communication with Game

#include "stdafx.h"
#include "Game.h"
#include "Thread.h"
#include "Engine.h"

#include "Com_Cmd.h"

using namespace IA;
using namespace SO::Com;
using namespace std;

/////////////////////////////////////////////////////////////////////////////////////////
// init
Engine::Engine(IA::Game* NewGame, ComService* Up) : IIComIO(Up)
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

/////////////////////////////////////////////////////////////////////////////////////////
// ICom
void Engine::cGetCommands(std::vector<SO::Base::Handle<SO::Base::ICmd> > &Commands)
{
	ICom_RegisterCmd(Commands, Engine, cmd_add, "add");
}
Handle<ICom>& Engine::cGetHandle()
{
	TryCreateHandle<Engine>("SOIA"); 
	return IIComIO::cGetHandle();
}

bool Engine::cmd_add(const SO::Base::Handle<ICom> &Caller, const std::vector<void*> &Args)
{
	Engine::MThread.AddLoops(1);
	return true;
}
