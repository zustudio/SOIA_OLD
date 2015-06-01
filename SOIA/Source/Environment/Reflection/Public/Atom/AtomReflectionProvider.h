
#pragma once

#include "AtomReflection.h"
#include "ReflectionFactory.h"

#include <vector>

#include "RPointer.h"

namespace Environment
{
	class LIBIMPEXP AtomReflectionProvider
	{
	public:
		AtomReflectionProvider();
		AtomReflection* GetReflection(const std::string& InTypeName);

		template<typename Type> void Reflect()
		{/*
			decltype(std::declval<decltype(Atom::IsAtomType)>()) t = &b;*/
			factory.Add<Type>(Reflections, 0);

			/*std::string TypeID = typeid(Type).name();
			if (!GetReflection(TypeID))
			{
				Reflections.push_back(factory.Create<Type>());
			}*/
		}
		ReflectionFactory factory;

	private:
		std::vector<AtomReflection*> Reflections;
	};
}
