
#pragma once

#include <type_traits>

namespace Environment
{
#ifdef _MSC_VER
	template<typename TestType>
	struct HasMemberAccessOperator
	{
		__if_exists(TestType::operator->)
		{
			static constexpr const bool value = true;
		}
		__if_not_exists(TestType::operator->)
		{
			static constexpr const bool value = false;
		}
	};
#else
	template <typename T>
	struct HasMemberAccessOperator
	{
		template <class, class> class checker;

		template <typename C>
		static std::true_type test(checker<C, decltype(&C::operator->)> *);

		template <typename C>
		static std::false_type test(...);

		typedef decltype(test<T>(nullptr)) type;
		static const bool value = std::is_same<std::true_type, decltype(test<T>(nullptr))>::value;
	};
#endif
}