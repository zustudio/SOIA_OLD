#pragma once

namespace IA
{
	class Engine;
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

		///////////////////////////////////////////////////////////////
		// functions
		//--- runtime ---
		void Start();
		//--- init ---
		ConsoleService(IA::Engine* newEngine);
	};
}
