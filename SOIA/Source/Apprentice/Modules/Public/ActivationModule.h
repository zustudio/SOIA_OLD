
#pragma once

// include Super class
#include "Apprentice/Core/Public/Module.h"

namespace Apprentice
{
class ActivationModule : public Module
{
public:
	//////////////////////////////////////////////////////////////
	// Event definitions

	Environment::Event ERequest_ActivateNextModules;

	//////////////////////////////////////////////////////////////
	// Init

	ActivationModule();
	~ActivationModule();

	////////////////////////////////////////////////////////////////////
	// Commands
	Environment::RFunctionInterface* cmd_Activate;
private:
	bool rawcmd_Activate();
};
}
