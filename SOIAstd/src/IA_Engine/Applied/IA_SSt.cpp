
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

	*Current >> added1;

}


/////////////////////////////////////////////////////////////////////////////////////////
// variables
IData* Engine_SSt::getDataStart()
{
	return Knowledge;
}
