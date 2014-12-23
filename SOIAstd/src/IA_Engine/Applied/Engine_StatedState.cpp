
#include "SDL.h"
#include "Engine_StatedState.h"

using namespace IA;

////////////////////////////////////////////////////////////
// init
Engine_StatedState::Engine_StatedState(IA::Game* NewGame) : Engine(NewGame)
{
	SDL_start

	symbol Knowledge is 1475
		name("Knowledge")

		newsub test is 2001
			name("test")
		endsub

		newsub Action is 111
			name("Action")
		endsub

		newsub Result is 112
			name("Result")
		endsub

		newsub Visible is 113
			name("Visible")
		endsub

		newsub Current is 114
			name("Current")
		endsub
	endsymbol
	
}

Engine_StatedState::~Engine_StatedState()
{

}

void Engine_StatedState::Tick()
{

}
