
#pragma once

#include "RElement.h"
#include "Thread.h"

#include "RFunction.h"
#include "InPort.h"
#include "OutPort.h"

namespace Supervisor
{
	RCLASS(Pipe, Environment::RElement)
	class Pipe : public Pipe_Base, public Environment::Thread
	{
		RCLASS_BEGIN();

		Pipe(Environment::RFunction* = nullptr);

		virtual void Main() override;

		Environment::RFunction* TargetFunction;

		std::vector<InPort> Input;
		std::vector<OutPort> Output;

		RCLASS_END();
	};
}