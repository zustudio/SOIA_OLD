#pragma once

namespace IA
{
	class Data;
	class Game;
	class Engine
	{
	public:
		///////////////////////////////////////////////////////////////////
		// variables
		//---- constants ----
		static const int cAI_Options = 3;
		//---- data ----
		Data* Knowledge;
		//---- instances ----
		IA::Game* CurrentGame;
		//@TODO--> static Random* Generator = gcnew Random(60625);
		//---- threading ----
		int aAI_LoopsToDo;
		bool aAI_Exit;
		static Object* Lock = gcnew Object;


		///////////////////////////////////////////////////////////////////
		// functions
		//----  init   ----
		/*initializes AI Engine*/
		Engine(IA::Game* NewGame);
		//----  main   ----
		/* starts the Engine's loop*/
		virtual void Start();
		//---- ticking ----
		virtual void Tick();
		//----  rand   ----
		virtual int InfluencedRand(Collections::Generic::List<float>* Chances);
		virtual int InfluencedRand(array<float>* Chances);
		//----   io    ----
		IA::Data* IFuncResultOfAction(IA::Data* Output);
		//---- multi threading ----
		void MTAddTicks(int i);
		IA::Data* ReadData();
		void StopData();

	};

}