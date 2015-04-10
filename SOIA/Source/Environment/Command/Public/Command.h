
#pragma once

#include <vector>
#include <functional>

#include "VoidPointer.h"
using namespace SO::Base;

namespace Environment
{
class Command
{
public:
	virtual bool Execute(void* Caller, const std::vector<VoidPointer> &Args) const = 0;


	CommandExecutor* TargetObj;
	std::function<void(const CommandExecutor&, std::vector<VoidPointer>&)> TargetFunction;



};
}

