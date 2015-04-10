
// include Super class
#include "EventHandler.h"

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
