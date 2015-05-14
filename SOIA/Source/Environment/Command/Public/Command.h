
#pragma once

#include <vector>
#include <functional>

#include "CommandExecutor.h"

#include "Reflection/Type/Public/VoidPointer.h"
using namespace SO::Base;

namespace Environment
{
class Command
{
public:

	Command()

	virtual bool Execute(void* Caller, const std::vector<VoidPointer> &Args);


	CommandExecutor* TargetObj;
	std::function<void(const CommandExecutor&, const std::vector<VoidPointer>&)> TargetFunction;



};
}

