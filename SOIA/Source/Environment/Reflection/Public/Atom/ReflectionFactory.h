
#pragma once

#include "SimpleAtomReflection.h"
#include "VectorAtomReflectionTemplate.h"
#include "PointerReflectionTemplate.h"
#include "Atom.h"
#include <string>
#include <type_traits>

namespace Environment
{
	class LIBIMPEXP ReflectionFactory
	{
		template <typename T, typename _ = void>
		struct is_vector
		{
			static const bool value = false;
		};

		template<class T>
		struct is_vector<std::vector<T> >
		{
			static bool const value = true;
		};

	public:

		bool IsAdded(TypeID InType, const std::vector<AtomReflection*>& Reflections);

		template<typename Type, typename NOP>
		bool Add(std::vector<AtomReflection*>& Reflections, NOP)
		{
			return true;
		}

		template<typename Type>
		auto Add(std::vector<AtomReflection*>& Reflections, int) -> typename std::enable_if<std::is_base_of<Atom, Type>::value, bool>::type
		{
			if (!IsAdded(TypeID::FromType<Type>(), Reflections))
				Reflections.push_back(new SimpleAtomReflection<Type>(&Type::ToString, &Type::FromString));
			return true;
		}

		template<typename Type>
		auto Add(std::vector<AtomReflection*>& Reflections, int) -> typename std::enable_if<std::is_pointer<Type>::value, bool>::type
		{
			if (!IsAdded(TypeID::FromType<Type>(), Reflections))
			{
				Reflections.push_back(new PointerReflectionTemplate<Type>());
				Add<typename std::decay<decltype(*std::declval<Type>())>::type>(Reflections, 0);
			}
			return true;
		}

		template<typename Type>
		auto Add(std::vector<AtomReflection*>& Reflections, int) -> typename std::enable_if<is_vector<Type>::value, bool>::type
		{
			if (!IsAdded(TypeID::FromType<Type>(), Reflections))
			{
				Reflections.push_back(new VectorAtomReflectionTemplate<Type>());
				Add<typename Type::value_type>(Reflections, 0);
			}
			return true;
		}

		/*template<typename... Types>
		AtomReflection* Create() {return nullptr;}*/

	};
}
