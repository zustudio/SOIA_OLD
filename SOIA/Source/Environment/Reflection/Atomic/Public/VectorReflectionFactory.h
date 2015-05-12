
#pragma once

#include "Environment/Reflection/Atomic/Classes/VectorAtomReflectionTemplate.h"
#include <string>

namespace Environment
{
	class DLLIMPEXP VectorReflectionFactory
	{
	public:
		static bool IsTypeAvailable(const std::string& InTypeID);

		template<typename Type> static AtomReflection* Create()
		{
			return new VectorAtomReflectionTemplate<Type>();
		}
	};
}
