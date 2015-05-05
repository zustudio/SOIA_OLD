
#pragma once

// include super class
#include "Environment/Reflection/Element/Public/RApplication.h"

// include SOIA
#include "Environment/Reflection/Element/Public/RFunction.h"
using namespace Environment;

// include std
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

namespace Supervisor
{
	class DLLIMPEXP ConsoleService : public RApplication
	{
	public:
		///////////////////////////////////////////////////////////////
		// functions
		//--- init ---
		ConsoleService(Environment::RContainer &InServices);
		//--- runtime ---
		virtual void Main() override;

		bool cmd_exit();
		/*Environment::TargetFunctionType cmd_echo;
		Environment::TargetFunctionType cmd_reply;*/
		bool cmd_create(const std::string &Name);

	protected:
		//----- input interpretation -----

		/// Returns vector of matching functions, as well as arguments to be applied to these.
		bool InterpretInput(const std::vector<std::string> &InInput, std::vector<RService*> &OutServices, std::vector<RFunctionInterface*> &OutFunctions, std::vector<Environment::VoidPointer> &OutArgs);

	private:
		///////////////////////////////////////////////////////////////
		// variables
		//--- external instances ---
		//- singular
		IA::Engine* CurrentEngine;

		//--- status ---
		bool bLoop;
		std::string LastTalker;
		
	};
}
