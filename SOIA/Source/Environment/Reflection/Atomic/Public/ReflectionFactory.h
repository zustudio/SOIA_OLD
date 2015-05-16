
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


//	template<class Type, typename Enable = void>
//	class Factory
//	{};
//
//	/*template<class T>
//	class Factory<T, typename std::enable_if_t<std::is_same<decltype(std::declval<decltype(T::IsAtomType)>()), bool&&>::value, bool>>
//	{
//	public:
//		int DoSomething()
//		{
//			return 1;
//		}
//	};
//*/
//	template<class T>
//	class Factory<T, typename std::enable_if<true/*std::is_pointer<T>::value*/>::type >
//	{
//	public:
//		int DoSomething()
//		{
//			return 2;
//		}
//	};






















	class DLLIMPEXP ReflectionFactory
	{

	public:
		static bool IsTypeAvailable(const std::string& InTypeID);


		//// the partial specialization of A is enabled via a template parameter
		//template<class T, class Enable = void>
		//struct A {}; // primary template

		//template<class T>
		//class A<T, typename std::enable_if<std::is_floating_point<T>::value >::type>
		//{
		//}; // specialization for floating point types

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

		template<typename Type>
		bool Add(std::vector<AtomReflection*>& Reflections, ...)
		{
			return false;
		}

		template<typename Type>
		bool Add(std::vector<AtomReflection*>& Reflections, int, typename Type::IsAtomType* p = nullptr)
		{
			if (!IsAdded(TypeID::FromType<Type>(), Reflections))
				Reflections.push_back(new SimpleAtomReflection<Type>(&Type::ToString, &Type::FromString));
			return true;
		}

		template<typename Type>
		std::enable_if_t<std::is_pointer<Type>::value, bool> Add(std::vector<AtomReflection*>& Reflections, int)
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
				Add<Type::value_type>(Reflections, 0);
			}
			return true;
		}

		template<typename... Types>
		AtomReflection* Create() {return nullptr;}

		
//		template<typename Type, typename = typename Type::IsAtomType >
//		AtomReflection* Create()
//		{
//			return new SimpleAtomReflection<Type>(&Type::ToString, &Type::FromString);
//		}
//		template<typename Type, typename = decltype(*std::declval<Type&>(), bool())>
//		AtomReflection* Create()
//		{
//			return new PointerReflectionTemplate<Type>();
//		}
//		template<typename Type, typename = decltype(std::declval<typename Type::value_type>(), bool())>
//		AtomReflection* Create()
//		{
//			return new VectorAtomReflectionTemplate<Type>();
//		}
//
//		template<typename Type, typename decltype(std::declval<IsTrue<!std::is_pointer<Type>::value && !std::is_class<Type>::value>::Yes*>(), void())* p = nullptr>
//			AtomReflection* Create()
//		{
//			return nullptr;
//		}
	};
}
