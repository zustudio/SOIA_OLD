
#pragma once

#include "Environment/Reflection/Atomic/Classes/VectorAtomReflectionTemplate.h"
#include "Environment/Reflection/Atomic/Classes/PointerReflectionTemplate.h"
#include <string>

namespace Environment
{
	class DLLIMPEXP ReflectionFactory
	{
	public:
		static bool IsTypeAvailable(const std::string& InTypeID);

		template<typename Type> static AtomReflection* Create(typename Type::const_iterator* = nullptr)
		{
			return new VectorAtomReflectionTemplate<Type>();
		}
		template<typename Type> static AtomReflection* Create()
		{
			return new PointerReflectionTemplate<Type>();
		}
	};
}
