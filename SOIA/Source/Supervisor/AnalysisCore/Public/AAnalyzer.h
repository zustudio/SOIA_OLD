
#pragma once

#include "RElement.h"

#include "FunctionInterface.h"
#include "InPort.h"
#include "OutPort.h"

namespace Supervisor
{
	RCLASS(AAnalyzer, Environment::RElement)
	class AAnalyzer : public AAnalyzer_Base
	{
		RCLASS_BEGIN();

		AAnalyzer();

	protected:
		void SetAnalyzerFunction(Environment::FunctionInterface*);

		std::vector<InPort> Input;
		std::vector<OutPort> Output;

		RCLASS_END();
	};
}