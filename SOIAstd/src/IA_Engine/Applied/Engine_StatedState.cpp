#include "stdafx.h"

#include "SDL.h"
#include "Game_StatedState.h"
#include "Engine_StatedState.h"

using namespace IA;

////////////////////////////////////////////////////////////
// init
Engine_StatedState::Engine_StatedState(IA::Game* NewGame) : Engine(NewGame)
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

Engine_StatedState::~Engine_StatedState()
{

}

void Engine_StatedState::Tick()
{
	SDL_start

	newsymbol added1 is 2
		newsub added2 is *IFuncResultOfAction(added1)
		endsub
	endsymbol



	*Current >> added1;
}

Data_StatedState* Engine_StatedState::IFuncResultOfAction(Data_StatedState* Output)
{
	Data_StatedState* Result = ((Game_StatedState*)CurrentGame)->IFuncResultOfAction(Output);

	std::cout << "[IA]: ";
	std::cout << std::to_string(Output->Data::Content);
	std::cout << "->";
	std::cout << std::to_string(Result->Data::Content);
	std::cout << "\n";

	return Result;
}
