
#pragma once

#include "AtomReflectionInterface.h"

#include <vector>

namespace Environment
{
	class DLLIMPEXP AtomReflectionProvider
	{
	public:
		AtomReflectionProvider();
		AtomReflectionInterface* GetReflection(const std::string& InTypeName);

	private:
		std::vector<AtomReflectionInterface*> Reflections;
	};
}