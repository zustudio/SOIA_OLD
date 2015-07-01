
#pragma once

//include Super class
#include "Apprentice/Core/Public/ModuleConfiguration.h"

#include "Apprentice/Modules/Public/ActivationModule.h"

namespace Apprentice
{
class SStModuleConfiguration : public ModuleConfiguration
{
public:
	//////////////////////////////////////////////////////////////
	// Init

	SStModuleConfiguration();
	virtual ~SStModuleConfiguration();

	//////////////////////////////////////////////////////////////
	// Modules
	ActivationModule MyActivationModule;

	//////////////////////////////////////////////////////////////
	// event handlers
	bool eventhandler_RequestActivateNextModules(Environment::EventDetails*);

};
}
