
#pragma once

//include Super class
#include "ModuleConfiguration.h"

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
	// Events

	virtual void Handle(const Environment::Event &InEvent) override;

};
}
