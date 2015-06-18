
#pragma once

#include "RElement.h"

#include "FunctionInterface.h"
#include "InPort.h"
#include "OutPort.h"

namespace Supervisor
{
	RCLASS(Pipe, Environment::RElement)
	class Pipe : public Pipe_Base
	{
		RCLASS_BEGIN();

		Pipe();

	protected:
		bool SetAnalyzerFunction(Environment::FunctionInterface*);

		std::vector<InPort> Input;
		std::vector<OutPort> Output;

		RCLASS_END();
	};
}