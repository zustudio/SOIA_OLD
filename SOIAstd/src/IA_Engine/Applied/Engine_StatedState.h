#pragma once

#include "Engine.h"

namespace IA
{
	class Game;
	class Data_StatedState;
	class Engine_StatedState : public Engine
	{
	public:
		///////////////////////////////////////
		// vars
		Data_StatedState* Current;

		///////////////////////////////////////
		// functions
		//----  init   ----
		Engine_StatedState(IA::Game* newGame);
		virtual ~Engine_StatedState();
		//----  tick   ----
		virtual void Tick() override;
	};
}