
#pragma once

#include "AtomReflection.h"
#include "ReflectionFactory.h"

#include <vector>

namespace Environment
{
	class LIBIMPEXP AtomReflectionProvider
	{
	public:
		AtomReflectionProvider();
		virtual ~AtomReflectionProvider();

		AtomReflection* GetReflection(const std::string& InTypeName);
		std::vector<TypeID> GetTypeList();

		template<typename Type> void Reflect()
		{
			factory.Add<Type>(Reflections, 0);

		}
		ReflectionFactory factory;

	private:
		std::vector<AtomReflection*> Reflections;
	};
}
