
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

		sub Action is 111
		setname("Action")
		endsub

		sub Result is 112
		setname("Result")
		endsub

		sub Visible is 113
		setname("Visible")
		endsub

		sub Current is 114
		setname("Current")
		endsub
		endsymbol

		newsymbol nDat is 2
		endsymbol

		newsymbol nDat2 is 3
		endsymbol
	*Action >> nDat;
	*Action >> nDat2;

}

Engine_SSt::~Engine_SSt()
{

}

void Engine_SSt::Tick()
{
	SDL_start

	newsymbol added1 is 2
		newsub added2 is(*IFuncResultOfAction(added1))[0]
		endsub
	endsymbol

	newsymbol t1 is 3
	endsymbol
	*Current >> added1;
	*Current >> t1;

	int sim = Action->llink(Current, 2);
	std::string text = std::to_string(sim);
	std::cout << text;

}


/////////////////////////////////////////////////////////////////////////////////////////
// variables
IData* Engine_SSt::getDataStart()
{
	return Knowledge;
}
