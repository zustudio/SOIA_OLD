
#pragma once

#include "Port.h"

#include <deque>

namespace Supervisor
{
	class InPort : public Port
	{
	public:
		InPort(Environment::TypeID InType);

		virtual bool Write(const Environment::VoidPointer& InData) override;
		virtual bool Read(Environment::VoidPointer& InData) override;

	protected:
		std::deque<Environment::VoidPointer> InputBuffer;
	};
}
