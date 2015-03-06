#pragma once

//Super classes
#include "Thread.h"
#include "IIComIO.h"
#include "IIDebuggable.h"

#include <vector>
#include <iostream>
#include "Game.h"
#include "ComService.h"
#include "Statistics.h"


namespace IA
{
	class Data;
	class Game;
	class Engine : public SO::Thread, public SO::Com::IIComIO, protected SO::Debug::IIDebuggable
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
		std::vector<int>* IFuncResultOfAction(IData* Output);

		///////////////////////////////////////////////////////////////////
		// commands
		T_com_cmd_func cmd_add;
		T_com_cmd_func cmd_break;
		T_com_cmd_func cmd_continue;

		///////////////////////////////////////////////////////////////////
		// ICom interface
		virtual void cGetCommands(std::vector<SO::Base::Handle<SO::Base::ICmd> > &Commands) override;
		virtual Handle<SO::Com::ICom>& cGetHandle() override;

		///////////////////////////////////////////////////////////////////
		// IDebuggable interface
		virtual void ii_Break(const std::string &Message = "") override;

		///////////////////////////////////////////////////////////////////
		// variables
		//---- access to properties ----
	public:
		virtual IData* getDataStart() = 0;
		virtual SO::Debug::Statistics& getResultStatistics() = 0;
		virtual SO::Debug::Statistics& getActionStatistics() = 0;
		//---- instances ----
		IA::Game* CurrentGame;

	};

}
