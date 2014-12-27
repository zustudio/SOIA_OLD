#pragma once
#include <vector>
#include "Game.h"
#include "Thread.h"


namespace IA
{
	class Data;
	class Game;
	class Engine : public SO::Thread
	{
	public:
		///////////////////////////////////////////////////////////////////
		// variables
		//---- data ----
		Data* Knowledge;
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
		Data* IFuncResultOfAction(Data* Output)
		{
			Data* Result = CurrentGame->IFuncResultOfAction(Output);

			std::cout << "[IA]: ";
			std::cout << std::to_string(Output->Content);
			std::cout << "->";
			std::cout << std::to_string(Result->Content);
			std::cout << "\n";

			return Result;
		}

	};

}
