
// include Super class
#include "Event/Public/EventHandler.h"

#pragma once

namespace Apprentice
{
class ModuleConfiguration : public Environment::EventHandler
{
public:
	//////////////////////////////////////////////////////////////
	// Init

	ModuleConfiguration();
	virtual ~ModuleConfiguration();

	//////////////////////////////////////////////////////////////
	// Events

};
}
