
#pragma once

// include Super class
#include "Core/Public/Module.h"

namespace Apprentice
{
class ActivationModule : public Module
{
public:
	//////////////////////////////////////////////////////////////
	// Event definitions

	static Environment::Event ERequest_ActivateNextModules;

	Commands* CommandList;

	//////////////////////////////////////////////////////////////
	// Init

	ActivationModule();
	~ActivationModule();

};
}
