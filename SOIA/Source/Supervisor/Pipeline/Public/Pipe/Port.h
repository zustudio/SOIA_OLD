
#pragma once

#include "VoidPointer.h"
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
		Port(PortConfiguration InConfiguration, Environment::TypeID InType);

		virtual bool Write(const Environment::VoidPointer& InData) = 0;
		virtual bool Read(Environment::VoidPointer& InData) = 0;

		bool Pair(Port* InPartner);
		Environment::TypeID GetType();


	protected:
		Port* Partner;
		PortConfiguration Configuration;
		Environment::TypeID Type;
		std::string Description;
	};
}
