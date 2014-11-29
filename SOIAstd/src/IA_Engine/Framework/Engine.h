#pragma once
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
		//@TODO--> static Random* Generator = gcnew Random(60625);

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
