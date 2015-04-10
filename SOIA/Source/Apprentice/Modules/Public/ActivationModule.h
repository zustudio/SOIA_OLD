
#pragma once

// include Super class
#include "Module.h"

namespace Apprentice
{
class ActivationModule : public Module
{
public:
	//////////////////////////////////////////////////////////////
	// Event definitions

	static Environment::Event ERequest_ActivateNextModules;

	//////////////////////////////////////////////////////////////
	// Init

	ActivationModule();
	~ActivationModule();

};
}
