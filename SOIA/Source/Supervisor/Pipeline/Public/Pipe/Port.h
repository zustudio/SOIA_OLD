
#pragma once

#include "VoidPointer.h"
#include "Thread.h"
#include "TypeID.h"
#include <string>

namespace Supervisor
{
	enum class PortConfiguration : int
	{
		Input,
		Output
	};

	class Port
	{
	public:
		Port(Environment::Thread* InOwner, PortConfiguration InConfiguration, Environment::TypeID InType);

		virtual bool Write(const Environment::VoidPointer& InData) = 0;
		virtual bool Read(Environment::VoidPointer& InData) = 0;

		void WakeUp();

		bool Pair(Port* InPartner);
		Environment::TypeID GetType();


	protected:
		Port* Partner;
		Environment::Thread* Owner;
		PortConfiguration Configuration;
		Environment::TypeID Type;
		std::string Description;
	};
}
