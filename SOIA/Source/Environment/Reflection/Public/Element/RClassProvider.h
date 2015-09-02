/// Intelligence Project - SOIA
/// \file
/// \copyright
///

#pragma once

#include "RClass.h"

#include <vector>

namespace Environment
{
	class RElement;

	/// \brief		Gives access to registered 'RClass'es.
	/// \details	Registered classes can be accessed via their type.
	class LIBIMPEXP RClassProvider
	{
	public:
		RClassProvider();
		~RClassProvider();


		template<typename RType1, typename RType2, typename... TailTypes>
		void RegisterList()
		{
			RegisterList<RType1>();
			RegisterList<RType2, TailTypes...>();
		}

		template<typename RType>
		void RegisterList()
		{
			Register<RType>();
		}

		template<typename RType>
		auto Register() -> typename std::enable_if<std::is_abstract<RType>::value>::type
		{
			RegisterAbstract<RType>();
		}

		template<typename RType>
		auto Register() -> typename std::enable_if<!std::is_abstract<RType>::value>::type
		{
			RegisterConcrete<RType>();
		}

		template<typename RType>
		void RegisterAbstract()
		{
			RegisterInternal(new RAbstractClass(TypeID::FromType<RType::Type>(), TypeID::FromType<RType::Super::Type>()));
		}

		template<typename RType>
		void RegisterConcrete()
		{
			RegisterInternal(new RClassTemplate<RType>(TypeID::FromType<RType::Type>(), TypeID::FromType<RType::Super::Type>()));
		}

		void RegisterInternal(RClass* InClass);

		RClass* GetClass(const TypeID& InType);
		std::vector<TypeID> GetTypeList();

	private:
		std::vector<RClass*> Classes;

	};
}