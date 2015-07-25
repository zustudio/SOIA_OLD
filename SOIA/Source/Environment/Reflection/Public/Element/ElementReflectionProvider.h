
#pragma once

#include "RClass.h"

#include <vector>

namespace Environment
{
	class RElement;

	class LIBIMPEXP ElementReflectionProvider
	{
	public:
		ElementReflectionProvider();
		~ElementReflectionProvider();

		void Register_DEPRECATED(RClass* InClass);

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
			RegisterInternal(new RAbstractClass(TypeID::FromType<RType::Type>(), TypeID::FromType<RType::Super::Type>()));
		}

		template<typename RType>
		auto Register() -> typename std::enable_if<!std::is_abstract<RType>::value>::type
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