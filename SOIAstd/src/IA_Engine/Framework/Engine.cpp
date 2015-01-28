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
	TryCreateHandle("SOIA"); 
	return IIComIO::cGetHandle();
}

bool Engine::cmd_add(const SO::Base::Handle<ICom> &Caller, const std::vector<VoidPointer> &Args)
{
	//ICom_GetSingleArg(int, Num, Args, 0, false);
	if (Args.size() > 0)
	{

		int* Num = Args[0].CastTo<int>();
		std::string* NumText = Args[0].CastTo<std::string>();

		if (Num)
		{
			MThread.AddLoops(*Num);
			return true;
		}
		//ICom_GetSingleArg(std::string, NumText, Args, 0, false);
		if (NumText)
		{
			int times = std::atoi(NumText->c_str());
			MThread.AddLoops(times);
			return true;
		}
	}
	Engine::MThread.AddLoops(1);
	return true;
}
