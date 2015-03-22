//c Maxim Urschumzew
//Base class for different ai engines, to be inherited - provides framework for communication with Game

#include "stdafx.h"
#include "Game.h"
#include "Thread.h"
#include "Engine.h"

#include "Com_Cmd.h"

#include <mutex>
#include <condition_variable>
#include <thread>


using namespace IA;
using namespace SO::Com;
using namespace SO::Debug;
using namespace std;

/////////////////////////////////////////////////////////////////////////////////////////
// init
Engine::Engine(IA::Game* NewGame, ComService* Up) : IIComIO(Up), IIDebuggable(Up)
{
	CurrentGame = NewGame;
}
Engine::~Engine()
{

}
int Engine::Init()
{
	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////
// tick
void Engine::Tick()
{
	IData* test;

	std::cout << "[IA-Engine]: no engine implementation";
}

/////////////////////////////////////////////////////////////////////////////////////////
// commands
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

bool Engine::cmd_break(const Handle<ICom> &Caller, const std::vector<VoidPointer> &Args)
{
	//backup current bEnabled
	bool bBackup = MThread.bEnabled;
	//start lock
	bool* bWake = &MThread.bEnabled;
	*bWake = false;
	std::unique_lock<std::mutex> lock(*MThread.m);
	MThread.cv->wait(lock, [&bWake] { return *bWake; });

	//delock thread
	lock.unlock();
	//restore backup
	MThread.bEnabled = bBackup;
	return true;
}
bool Engine::cmd_continue(const Handle<ICom> &Caller, const std::vector<VoidPointer> &Args)
{
	MThread.bEnabled = true;
	MThread.cv->notify_one();
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
// ICom
void Engine::cGetCommands(std::vector<SO::Base::Handle<SO::Base::ICmd> > &Commands)
{
	IIComIO::cGetCommands(Commands);

	ICom_RegisterCmd(Commands, Engine, cmd_add, "add");
	ICom_RegisterCmd(Commands, Engine, cmd_break, "break");
	ICom_RegisterCmd(Commands, Engine, cmd_continue, "continue");
}
Handle<ICom>& Engine::cGetHandle()
{
	TryCreateHandle("SOIA"); 
	return IIComIO::cGetHandle();
}

///////////////////////////////////////////////////////////////////////////
// IDebuggable interface
void Engine::ii_Break(const std::string &Message)
{
	if (GetBreakEnabled())
	{
		if (Message != "")
		{
			ii_Log(EDebugLevel::Warning, std::string("[BREAK] ") + Message);
		}
		cmd_break(Handle<ICom>(), {});
	}
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
	ii_Log(EDebugLevel::Info_MainFunction, logtext);

	return Result;
}