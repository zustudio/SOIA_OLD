#pragma once
#include <vector>
#include <iostream>
#include "Game.h"
#include "Thread.h"


namespace IA
{
	class Data;
	class Game;
	class Engine : public SO::Thread
	{
		///////////////////////////////////////////////////////////////////
		// variables
		//---- data ----
	public:
		virtual IData* getDataStart() = 0;
		//---- instances ----
		IA::Game* CurrentGame;

		///////////////////////////////////////////////////////////////////
		// functions
		//----  init   ----
		/*initializes AI Engine*/
		Engine(IA::Game* NewGame);
		virtual ~Engine();
		//---- ticking ----
		virtual void Tick() override;
		//----  rand   ----
		virtual int InfluencedRand(std::vector<float> &Chances);
		//virtual int InfluencedRand(array<float>* Chances);
		//----   io    ----
		std::vector<int>* IFuncResultOfAction(IData* Output)
		{
			std::vector<int>* Result = CurrentGame->IFuncResultOfAction(Output);

			std::cout << "[IA]: ";
			std::cout << int(*Output);
			std::cout << "->";
			std::cout << (*Result)[0];
			std::cout << "\n";

			return Result;
		}

	};

}
