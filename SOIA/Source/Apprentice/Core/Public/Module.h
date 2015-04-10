
// include Super class
#include "EventDispatcher.h"

#pragma once

namespace Apprentice
{
class Module : public Environment::EventDispatcher
{
public:
	////////////////////////////////////////////
	// Init

	Module(Environment::EventHandler* InModuleConfiguration);
	virtual ~Module();

	////////////////////////////////////////////
	// Action System

};
}
