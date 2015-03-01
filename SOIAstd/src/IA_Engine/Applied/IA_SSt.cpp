
#include "stdafx.h"

#include "IA_SSt.h"

#include "MeaningService.h"
#include "Com_Cmd.h"

using namespace IA;
using namespace SO::Base;
using namespace SO::Com;
using namespace SO::Debug;
using namespace SO::MeaningStream;

//TEST
#define DownChild(data, num)	(data->getConnected(num, LinkType::T_NormLink | LinkType::Downlink))

////////////////////////////////////////////////////////////
// init
Engine_SSt::Engine_SSt(IA::Game* NewGame, SO::Com::ComService* ComCenter) : Engine(NewGame, ComCenter)
{
	// init class
	ActionStats = Statistics();
	ResultStats = Statistics();

	// init data
	SDL_start(true)

	symbol Knowledge is(1475)
		setname("Knowledge")

		sub Action isllist(0, 0, 1, 2)
			setname("Action")
		endsub

		sub Result isllist(0, 1, 1, 1)
			setname("Result")
		endsub

		sub Visible isllist(0, 1, 2, 0)
			setname("Visible")
		endsub

		sub Current is(1114)
			setname("Current")
		endsub
	endsymbol


	const int max = 4;
	for (int i = 0; i < max; i++)
	{
		*DownChild(Action, i) >> DownChild(Result, i);
		*DownChild(Result, i) >> DownChild(Visible, i);
		if (i + 1 < max)
		{
			*DownChild(Visible, i) >> DownChild(Action, i + 1);
		}
	}

	for (int i = 0; i < 2; i++)
	{
		std::vector<VoidPointer> Args;
		Engine* cast_Engine = static_cast<Engine*>(this);
		Args.push_back(*cast_Engine);
		cSend(Handle<ICom>(nullptr, "MeaningSrvc"), Com_Cmd<MeaningService>(&MeaningService::cmd_convertdata), Args);
	}
}

Engine_SSt::~Engine_SSt()
{

}

/////////////////////////////////////////////////////////////////////////////////////////
// main loop
void Engine_SSt::Tick()
{

	ii_SetBreakPointsEnabled(false);
	ii_Break();

	static int i = 0;

	SDL_start(false)

	newsymbol action isdefault
		setname(std::string("X") + std::to_string(i))
		newsub result is(1)
		endsub
	endsymbol

	*Action >> action;
	*Result >> result;

	int n_CVisible = Visible->getConnectedNum(LinkType::T_NormLink | LinkType::Downlink);
	Data_SSt* lastVisible = (Data_SSt*)(Visible->getConnected(n_CVisible - 1, LinkType::T_NormLink | LinkType::Downlink));

	*lastVisible >> action;

	ReIntegrate(action);

	//stats:
	ActionStats.AddValue(action->get());

	std::vector<int> input = *IFuncResultOfAction(action);

	result->set(input[0]);

	//stats:
	ResultStats.AddValue(result->get());

	newsymbol visible is(input[1])
	endsymbol

	*result >> visible;
	*Visible >> visible;

	i++;

	/*std::vector<VoidPointer> Args;
	Engine* cast_Engine = static_cast<Engine*>(this);
	Args.push_back(*cast_Engine);
	cSend(Handle<ICom>(nullptr, "MeaningSrvc"), Com_Cmd<MeaningService>(&MeaningService::cmd_convertdata), Args);*/
}

void Engine_SSt::ReIntegrate(Data_SSt* X)
{
	std::deque<Data_SSt*> similarityCandidates;

	int nSimCand = Action->getConnectedNum(LinkType::T_NormLink | LinkType::Downlink);
	for (int iSimCand = 0; iSimCand < nSimCand; iSimCand++)
	{
		Data_SSt* SimCand = (Data_SSt*)DownChild(Action, iSimCand);
		if (SimCand != X)
		{
			similarityCandidates.push_back(SimCand);
		}
	}

	X->set(SIM_Val_X + 1);

	nSimCand = similarityCandidates.size();
	for (int iSimCand = 0; iSimCand < nSimCand; iSimCand++)
	{
		int llresult = X->llink(similarityCandidates[iSimCand], 2);
		X->bLLinked = false;
		ii_Log(EDebugLevel::Info_Loop, "linking " + std::to_string((int)(*X)) + " \tto "  + std::to_string((int)(*similarityCandidates[iSimCand])) + " \t=> " + std::to_string(llresult));
	}

	X->set(SIM_Val_X);
	X->CollapseOpenLLinks();
	int newVal = (int)(*X);

	ii_Log(EDebugLevel::Info_MainFunction, "New Action is " + std::to_string(newVal));
}


/////////////////////////////////////////////////////////////////////////////////////////
// variables
IData* Engine_SSt::getDataStart()
{
	return Knowledge;
}
Statistics& Engine_SSt::getActionStatistics()
{
	return ActionStats;
}
Statistics& Engine_SSt::getResultStatistics()
{
	return ResultStats;
}
