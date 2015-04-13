
#pragma once

namespace Environment
{
	
	typedef bool(CommandExecutor::* TCommandFunction)();

class CommandExecutor
{
public:
	struct Commands
	{
		Command DoSomething;
	};

	TCommandFunction h;
};
	
}
