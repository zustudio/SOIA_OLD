#pragma once
#include <vector>
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
		IA::Data* IFuncResultOfAction(IA::Data* Output);

	};

}
