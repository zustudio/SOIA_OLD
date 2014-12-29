#include "IA_SSt.h"

#include "stdafx.h"

#include "SDL.h"
#include "Game_StatedState.h"

using namespace IA;

////////////////////////////////////////////////////////////
// init
Engine_SSt::Engine_SSt(IA::Game* NewGame) : Engine(NewGame)
{
	SDL_start

	symbol Knowledge is 1475
		name("Knowledge")

		sub Action is 111
			name("Action")
		endsub

		sub Result is 112
			name("Result")
		endsub

		sub Visible is 113
			name("Visible")
		endsub

		sub Current is 114
			name("Current")
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