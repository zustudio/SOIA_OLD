
#pragma once

//interface
#include "IIComIO.h"

//properties
#include "ComService.h"
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
		ConsoleService(IA::Engine* newEngine, SO::Com::ComService* NewUp);
		//--- runtime ---
		void Start();
		//--- create window ---
		template <class WClass> void AddWindow(WClass *Window)
		{
			Threads.push_back(new std::thread(&WClass::Start, Window));
			Windows.push_back(Window);
		}
		//--- ICom Interface ---
		virtual void cGetCommands(std::vector<Handle<ICmd> > &Commands) override;
		virtual Handle<ICom>& cGetHandle() override;

		T_com_cmd_func cmd_echo;
		T_com_cmd_func cmd_create;
		/*bool cmd_echo(const Handle<ICom> &Caller, const std::vector<void*> &Args);*/
		//bool cmd_create(const Handle<ICom> &Caller, const std::vector<void*> &Args);

	private:
		///////////////////////////////////////////////////////////////
		// variables
		//--- external instances ---
		IA::Engine* CurrentEngine;
		std::deque<SO::Window*> Windows;
		std::deque<std::thread*> Threads;
		SO::Com::ComService* ComCenter;


		
	};
}
