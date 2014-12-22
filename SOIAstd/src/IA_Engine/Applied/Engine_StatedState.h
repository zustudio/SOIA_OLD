#pragma once

#include "Engine.h"

namespace IA
{
	class Game;
	class Engine_StatedState : public Engine
	{
	public:
		///////////////////////////////////////
		// functions
		//----  init   ----
		Engine_StatedState(IA::Game* newGame);
		virtual ~Engine_StatedState();
		//----  tick   ----
		virtual void Tick() override;
	};
}