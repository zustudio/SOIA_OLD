
#pragma once

#include "PreProcessor/Classes/PrivateDefinitions.h"

// include class
#include "Command/Public/Command.h"
using namespace Environment;

bool Command::Execute(void* Caller, const std::vector<VoidPointer> &Args)
{
	TargetFunction(*TargetObj, Args);
}