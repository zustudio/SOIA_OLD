
#include "stdafx.h"
#include "SDL.h"

#include "IA_SSt.h"

#include "MeaningService.h"
#include "Com_Cmd.h"

using namespace IA;
using namespace SO::Base;
using namespace SO::Com;
using namespace SO::MeaningStream;

////////////////////////////////////////////////////////////
// init
Engine_SSt::Engine_SSt(IA::Game* NewGame, SO::Com::ComService* ComCenter) : Engine(NewGame, ComCenter)
{
	SDL_start(true)

		symbol Knowledge is(1475)
		setname("Knowledge")



		/*newsub test0 is(90)
		setname("test0")
		newsub test0_0 is(900)
		setname("test0_0")
		newsub test0_0_0 isllist(100, 101, 102, 103)
		newsub hor1 is(111)
		newsub hor2 is(112)
		endsub
		endsub
		setname("test0_0_0")
		endsub
		endsub
		endsub



		newsub test1 isllist(2, 3, 4, 5)
		setname("test1")
		endsub

		newsub test2 isllist(6,7,8,9)
		setname("test2")
		endsub

		newsub test3 is(112)
		setname("test3")
		endsub*/

		sub Action isllist(0, 1, 2, 3)
		setname("Action")
		endsub

		sub Result isllist(0, 1, 1, 1)
		setname("Result")
		endsub

		sub Visible isllist(1, 2, 3, 0)
		setname("Visible")
		endsub

		sub Current is(1114)
		setname("Current")
		endsub
		endsymbol


		const int max = 4;
	for (int i = 0; i < max; i++)
	{
		*((*Action)[i]) >> (*Result)[i];
		*((*Result)[i]) >> (*Visible)[i];
		if (i + 1 < max)
		{
			*((*Visible)[i]) >> (*Action)[i + 1];
		}
	}

	/*newsymbol nDat is 2
	endsymbol

	newsymbol nDat2 is 3
	endsymbol
	*Action >> nDat;
	*Action >> nDat2;*/
	std::vector<VoidPointer> Args;
	Engine* cast_Engine = static_cast<Engine*>(this);
	Args.push_back(*cast_Engine);
	cSend(Handle<ICom>(nullptr, "MeaningSrvc"), Com_Cmd<MeaningService>(&MeaningService::cmd_convertdata), Args);

//	std::vector<VoidPointer> SDLARGS;
//	SDLARGS.push_back(VoidPointer(std::string("SDLcreated")));
//	SDLARGS.push_back(VoidPointer(std::string("")))
//	SDLARGS.push_back(VoidPointer(Knowledge));
//
//	cSend(Handle<ICom>(nullptr, "MeaningSrvc"), Com_Cmd<MeaningService>(&MeaningService::cmd_addgroupstrings), SDLARGS);

	//cSend("MeaningSrvc", "addgroupstrings", "SDLcreated", "Equal", "Knowledge", " ", "DataPoints");
	//cSend("MeaningSrvc", "addgroupstrings", "SDLcreated", "Parentage", "Knowledge", "Knowledge", "List");
	
}

Engine_SSt::~Engine_SSt()
{

}

/////////////////////////////////////////////////////////////////////////////////////////
// main loop
void Engine_SSt::Tick()
{

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

	std::vector<int> input = *IFuncResultOfAction(action);

	result->set(input[0]);

	newsymbol visible is(input[1])
	endsymbol


	*result >> visible;
	*Visible >> visible;

	/*int sim = Action->llink(Current, 2);
	std::string text = std::to_string(sim);
	std::cout << text;
*/
	i++;
	

	std::vector<VoidPointer> Args;
	Engine* cast_Engine = static_cast<Engine*>(this);
	Args.push_back(*cast_Engine);
	cSend(Handle<ICom>(nullptr, "MeaningSrvc"), Com_Cmd<MeaningService>(&MeaningService::cmd_convertdata), Args);
}

void Engine_SSt::ReIntegrate(Data_SSt* X)
{
	std::deque<Data_SSt*> similarityCandidates;

	/*int nCat = X->getConnectedNum();
	for (int iCat = 0; iCat < nCat; iCat++)
	{
		Data_SSt* Cat = (Data_SSt*)(*X)[iCat];
		int nSimCand = Cat->getConnectedNum();
		
		for (int iSimCand = 0; iSimCand < nSimCand; iSimCand++)
		{
			Data_SSt* SimCand = (Data_SSt*)(*Cat)[iSimCand];
			if (SimCand != X)
			{
				similarityCandidates.push_back(SimCand);
			}
		}
	}*/

	int nSimCand = Action->getConnectedNum();
	for (int iSimCand = 0; iSimCand < nSimCand; iSimCand++)
	{
		Data_SSt* SimCand = (Data_SSt*)(*Action)[iSimCand];
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
		std::cout << "[IA_SSt]: linking " << (int)(*X) << " \tto " << (int)(*similarityCandidates[iSimCand]) << " \t=> " << llresult << std::endl;
	}

	X->set(SIM_Val_X);
	int newVal = (int)(*X);
	std::cout << "[IA_SSt]: new Action is " << newVal << std::endl;
}


/////////////////////////////////////////////////////////////////////////////////////////
// variables
IData* Engine_SSt::getDataStart()
{
	return Knowledge;
}
