
#pragma once

#include "RElement.h"

namespace Supervisor
{
	RCLASS(RConversionPipes, Environment::RElement);
	class LIBIMPEXP RConversionPipes : public RConversionPipes_Base
	{
		RCLASS_BEGIN();

		RConversionPipes();

		RFUNCTION(pipe_1DoubleTo2Double)
			bool pipe_1DoubleTo2Double(const double& In, double& Out1, double& Out2);

		RFUNCTION(pipe_IntToString)
			bool pipe_IntToString(const int& In, std::string& Out);

		RCLASS_END();
	};
}