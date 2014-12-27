#pragma once

#include "Engine.h"

namespace IA
{
	class Game;
	class Data_StatedState;
	class Game_StatedState;
	class Engine_StatedState : public Engine
	{
	public:
		///////////////////////////////////////
		// vars
		Data_StatedState* Action;
		Data_StatedState* Result;
		Data_StatedState* Visible;
		Data_StatedState* Current;

		///////////////////////////////////////
		// functions
		//----  init   ----
		Engine_StatedState(IA::Game* newGame);
		virtual ~Engine_StatedState();
		//----  tick   ----
		virtual void Tick() override;

		Data_StatedState* IFuncResultOfAction(Data_StatedState* Output);
	};
}