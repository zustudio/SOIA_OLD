
#pragma once

#include "AtomReflection.h"
#include "ReflectionFactory.h"

#include <vector>

namespace Environment
{
	class DLLIMPEXP AtomReflectionProvider
	{
	public:
		AtomReflectionProvider();
		AtomReflection* GetReflection(const std::string& InTypeName);

		template<typename Type> void Reflect()
		{
			std::string TypeID = typeid(Type).name();
			if (!GetReflection(TypeID))
			{
				Reflections.push_back(ReflectionFactory::Create<Type>());
			}
		}

	private:
		std::vector<AtomReflection*> Reflections;
	};
}