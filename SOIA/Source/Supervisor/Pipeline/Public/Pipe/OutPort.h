
#pragma once

#include "Port.h"

namespace Supervisor
{
	class LIBIMPEXP OutPort : public Port
	{
	public:
		OutPort(Environment::Thread* InOwner, Environment::TypeID InType);

		virtual bool Write(const Environment::VoidPointer& InData) override;
		virtual bool Read(Environment::VoidPointer& InData) override;

	protected:
		Environment::VoidPointer CurrentOutput;
	};
}