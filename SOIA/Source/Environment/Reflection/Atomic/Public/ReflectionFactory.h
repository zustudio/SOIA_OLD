
#pragma once

#include "Environment/Reflection/Atomic/Classes/SimpleAtomReflection.h"
#include "Environment/Reflection/Atomic/Classes/VectorAtomReflectionTemplate.h"
#include "Environment/Reflection/Atomic/Classes/PointerReflectionTemplate.h"
#include "Atom.h"
#include <string>

namespace Environment
{
	template<bool b>
	struct IsTrue
	{

	};

	template<>
	struct IsTrue<true>
	{
		typedef bool Yes;
	};

	class DLLIMPEXP ReflectionFactory
	{

	public:
		static bool IsTypeAvailable(const std::string& InTypeID);

		template<typename Type> static AtomReflection* Create(typename Type::const_iterator* = nullptr)
		{
			return new VectorAtomReflectionTemplate<Type>();
		}
		template<typename Type> static AtomReflection* Create(typename Type::IsAtomType* = nullptr)
		{
			return new SimpleAtomReflection<Type>(&Type::ToString, &Type::FromString);
		}
		template<typename Type,	typename = decltype(*std::declval<Type&>(), void())> 
			static AtomReflection* Create()
		{
			return new PointerReflectionTemplate<Type>();
		}
		template<typename Type>
		static AtomReflection* Create(typename decltype(std::declval<IsTrue<!std::is_pointer<Type>::value && !std::is_class<Type>::value>::Yes*>(), void()) = nullptr)
		{
			return nullptr;
		}
		//template<typename Type, typename = decltype(std::declval<IsTrue<false>::No>() /*std::declval(IsTrue<!std::is_pointer<Type> && !std::is_class<Type> >::Yes)*/, void())>
		//	static AtomReflection* Create()		// fallback
		//{
		//	return nullptr;
		//}
	};
}
