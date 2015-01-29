#pragma once
#include <vector>
#include <iostream>
#include "Game.h"
#include "Thread.h"
#include "IIComIO.h"
#include "ComService.h"


namespace IA
{
	class Data;
	class Game;
	class Engine : public SO::Thread, public SO::Com::IIComIO
	{
	public:
		///////////////////////////////////////////////////////////////////
		// functions
		//----  init   ----
		/*initializes AI Engine*/
		Engine(IA::Game* NewGame, SO::Com::ComService* Up);
		virtual ~Engine();
		virtual int Init() override;
		//---- ticking ----
		virtual void Tick() override;
		//----   io    ----
		std::vector<int>* IFuncResultOfAction(IData* Output)
		{
			std::vector<int>* Result = CurrentGame->IFuncResultOfAction(Output);

			std::cout << "[IA]: ";
			std::cout << int(*Output);
			std::cout << "->";

			std::cout << (*Result)[0];
			for (int i = 1; i < Result->size(); i++)
			{
				std::cout << ", " << (*Result)[i];
			}
			std::cout << "\n";

			return Result;
		}

		///////////////////////////////////////////////////////////////////
		// ICom interface
		virtual void cGetCommands(std::vector<SO::Base::Handle<SO::Base::ICmd> > &Commands) override;
		virtual Handle<SO::Com::ICom>& cGetHandle() override;
		T_com_cmd_func cmd_add;

		///////////////////////////////////////////////////////////////////
		// variables
		//---- data ----
	public:
		virtual IData* getDataStart() = 0;
		//---- instances ----
		IA::Game* CurrentGame;

	};

}
