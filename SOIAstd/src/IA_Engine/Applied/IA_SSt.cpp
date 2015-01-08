
#include "stdafx.h"
#include "SDL.h"

#include "IA_SSt.h"

using namespace IA;

////////////////////////////////////////////////////////////
// init
Engine_SSt::Engine_SSt(IA::Game* NewGame) : Engine(NewGame)
{
	SDL_start

	symbol Knowledge is 1475
		setname("Knowledge")

		sub Action isllist(1, 3, 3, 4)
		setname("Action")
		endsub

		sub Result isllist(1, 1, 0, 0)
		setname("Result")
		endsub

		sub Visible isllist(3, 2, 3, 3)
		setname("Visible")
		endsub

		sub Current is 114
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

}

Engine_SSt::~Engine_SSt()
{

}

/////////////////////////////////////////////////////////////////////////////////////////
// main loop
void Engine_SSt::Tick()
{
	SDL_start

	newsymbol unknown isdefault
		newsub result is 1
		endsub
	endsymbol

	*Action >> unknown;
	*Result >> result;

	int n_CVisible = Visible->getConnectedNum();
	Data_SSt* lastVisible = (Data_SSt*)(*Visible)[n_CVisible - 1];

	*lastVisible >> unknown;

	ReIntegrate(unknown);

	/*int sim = Action->llink(Current, 2);
	std::string text = std::to_string(sim);
	std::cout << text;
*/
	
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
	std::cout << "[IA_SSt]: new Action is " << newVal;
}


/////////////////////////////////////////////////////////////////////////////////////////
// variables
IData* Engine_SSt::getDataStart()
{
	return Knowledge;
}
