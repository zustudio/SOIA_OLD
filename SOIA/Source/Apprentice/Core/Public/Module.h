
#pragma once

// include Super class
#include "Event/Public/EventDispatcher.h"
#include "Command/Public/CommandExecutor.h"


namespace Apprentice
{
class Module : public Environment::EventDispatcher, public Environment::CommandExecutor
{
public:
	////////////////////////////////////////////
	// Init

	Module(Environment::EventHandler* InModuleConfiguration);
	virtual ~Module();

	////////////////////////////////////////////
	// Action System

	struct Commands : Environment::CommandExecutor::Commands
	{
		Environment::TCommandFunction DoAnotherThing;
	};


};
}
