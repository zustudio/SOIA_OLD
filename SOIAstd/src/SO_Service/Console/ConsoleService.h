#pragma once

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
	class ConsoleService
	{
	public:
		///////////////////////////////////////////////////////////////
		// variables
		//--- external instances ---
		IA::Engine* CurrentEngine;
		std::deque<SO::Window*> Windows;
		std::deque<std::thread*> Threads;

		///////////////////////////////////////////////////////////////
		// functions
		//--- runtime ---
		void Start();
		//--- init ---
		ConsoleService(IA::Engine* newEngine);
		//--- create window ---
		template <class WClass> void AddWindow(WClass *Window)
		{
			Threads.push_back(new std::thread(&WClass::Start, Window));
			Windows.push_back(Window);
		}
	};
}
