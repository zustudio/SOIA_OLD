
#pragma once

#include "TypeTraits.h"
#include "AtomConverter.h"
#include "SimpleConverter.h"
#include "PointerConverter.h"
#include "VectorConverter.h"

#include <vector>
#include <type_traits>

namespace Environment
{
	class LIBIMPEXP AtomConverterProvider
	{
	public:
		AtomConverterProvider();
		virtual ~AtomConverterProvider();

		AtomConverter* GetConverter(const std::string& InTypeName);
		std::vector<TypeID> GetTypeList();

		template<typename Type> void Reflect()
		{
			Add<Type>(Converters, 0);
		}

	public:

		bool IsAdded(TypeID InType, const std::vector<AtomConverter*>& Converters);

		template<typename Type, typename NOP>
		bool Add(std::vector<AtomConverter*>& Converters, NOP)
		{
			return true;
		}

		template<typename Type>
		auto Add(std::vector<AtomConverter*>& Converters, int) -> typename std::enable_if<std::is_base_of<Atom, Type>::value, bool>::type
		{
			if (!IsAdded(TypeID::FromType<Type>(), Converters))
				Converters.push_back(new SimpleConverter<Type>(&Type::StaticToString, &Type::StaticToObject));
			return true;
		}

		template<typename Type>
		auto Add(std::vector<AtomConverter*>& Converters, int) -> typename std::enable_if<std::is_pointer<Type>::value, bool>::type
		{
			if (!IsAdded(TypeID::FromType<Type>(), Converters))
			{
				Converters.push_back(new PointerConverter<Type>());
				Add<typename std::decay<decltype(*std::declval<Type>())>::type>(Converters, 0);
			}
			return true;
		}

		template<typename Type>
		auto Add(std::vector<AtomConverter*>& Converters, int) -> typename std::enable_if<is_vector<Type>::value, bool>::type
		{
			if (!IsAdded(TypeID::FromType<Type>(), Converters))
			{
				Converters.push_back(new VectorConverter<Type>());
				Add<typename Type::value_type>(Converters, 0);
			}
			return true;
		}

	private:
		std::vector<AtomConverter*> Converters;
	};
}
