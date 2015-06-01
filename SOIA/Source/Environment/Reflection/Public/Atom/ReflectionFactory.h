
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

	public:
		static bool IsTypeAvailable(const std::string& InTypeID);

		bool IsAdded(TypeID InType, const std::vector<AtomReflection*>& Reflections)
		{
			for (auto reflection : Reflections)
			{
				if (reflection->IsType(InType))
				{
					return true;
				}
			}
			return false;
		}




		template<typename Type, typename NOP>
		bool Add(std::vector<AtomReflection*>& Reflections, NOP)
		{
			return true;
		}


		/*template<typename Type, int>
		typename std::enable_if<std::is_floating_point<Type>::value, bool>::type Add(std::vector<AtomReflection*>& Reflections)
		{
			return true;
		}*/

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
				Reflections.push_back(new PointerReflectionTemplate<Type>());
			return true;
		}

		template<typename Type>
		auto Add(std::vector<AtomReflection*>& Reflections, int) -> typename decltype( (std::declval(Type::const_pointer), false) )
		{
			if (!IsAdded(TypeID::FromType<Type>(), Reflections))
			{
				Reflections.push_back(new VectorAtomReflectionTemplate<Type>());
				Add<typename Type::value_type>(Reflections, 0);
			}
			return true;
		}










		/*template<typename Type>
		typename std::enable_if<std::is_floating_point<Type>::value, bool>::type Add(std::vector<AtomReflection*>& Reflections, int)
		{
			return true;
		}

		template<typename Type>
		bool Add(std::vector<AtomReflection*>& Reflections, int, typename Type::IsAtomType p = nullptr)
		{
			if (!IsAdded(TypeID::FromType<Type>(), Reflections))
				Reflections.push_back(new SimpleAtomReflection<Type>(&Type::ToString, &Type::FromString));
			return true;
		}

		template<typename Type>
		typename std::enable_if<std::is_pointer<Type>::value, bool>::type Add(std::vector<AtomReflection*>& Reflections, int)
		{
			if (!IsAdded(TypeID::FromType<Type>(), Reflections))
				Reflections.push_back(new PointerReflectionTemplate<Type>());
			return true;
		}

		template<typename Type>
		bool Add(std::vector<AtomReflection*>& Reflections, int, typename Type::const_pointer p = nullptr)
		{
			if (!IsAdded(TypeID::FromType<Type>(), Reflections))
			{
				Reflections.push_back(new VectorAtomReflectionTemplate<Type>());
				Add<typename Type::value_type>(Reflections, 0);
			}
			return true;
		}*/

		template<typename... Types>
		AtomReflection* Create() {return nullptr;}

	};
}
