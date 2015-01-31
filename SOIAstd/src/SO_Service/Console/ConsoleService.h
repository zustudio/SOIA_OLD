
#pragma once

//interface
#include "IIComIO.h"

//properties
#include "ComService.h"
#include "MeaningService.h"
#include <deque>

namespace IA
{
	class Engine;
}

namespace SO
{
	class Window;
}

namespace std
{
	class thread;
}

namespace SOIA
{
	class ConsoleService : public SO::Com::IIComIO
	{
	public:
		///////////////////////////////////////////////////////////////
		// functions
		//--- init ---
		ConsoleService();
		//--- runtime ---
		void Start();
		//--- ICom Interface ---
		virtual void cGetCommands(std::vector<Handle<ICmd> > &Commands) override;
		virtual Handle<ICom>& cGetHandle() override;
		//--- ICom commands ---
		T_com_cmd_func cmd_exit;
		T_com_cmd_func cmd_echo;
		T_com_cmd_func cmd_reply;
		T_com_cmd_func cmd_create;

	private:
		///////////////////////////////////////////////////////////////
		// variables
		//--- external instances ---
		//- singular
		IA::Engine* CurrentEngine;
		SO::Com::ComService* Srvc_Com;
		SO::MeaningStream::MeaningService* Srvc_MeanStrm;
		//- multiple
		std::deque<SO::Thread*> Threads;
		//std::deque<std::thread*> Threads;
		//--- status ---
		bool bLoop;
		
	};
}
