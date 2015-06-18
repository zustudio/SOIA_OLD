
#pragma once

#include "Port.h"

namespace Supervisor
{
	class OutPort : public Port
	{
	public:
		OutPort(TypeID InType);

		virtual bool Write(const Environment::VoidPointer& InData) override;
		virtual bool Read(Environment::VoidPointer& InData) override;

	protected:
		VoidPointer CurrentOutput;
	};
}