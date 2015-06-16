
#pragma once

#include "Port.h"

namespace Supervisor
{
	class OutPort : public Port
	{
		OutPort();

		virtual bool Write(const Environment::VoidPointer& InData) override;
		virtual bool Read(Environment::VoidPointer& InData) override;

	protected:
		VoidPointer CurrentOutput;
	};
}