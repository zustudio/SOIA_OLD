#pragma once

#include <vector>
#include <iostream>
#include "Game.h"

namespace IA
{
	class Game;
	class Engine
	{
	public:
		///////////////////////////////////////////////////////////////////
		// functions
		//----  init   ----
		/*initializes AI Engine*/
		Engine(IA::Game* NewGame);
		virtual ~Engine();
		//---- ticking ----
		virtual void Tick();
		//----   io    ----
		std::vector<int>* IFuncResultOfAction(IData* Output);

		///////////////////////////////////////////////////////////////////
		// variables
		//---- access to properties ----
	public:
		virtual std::string getEngineName() = 0;
		virtual IData* getDataStart() = 0;
		//---- instances ----
		IA::Game* CurrentGame;

	};

}
